#include <pistache/endpoint.h>
#include "MicrowaveEndpoint.h"

using namespace Pistache;

MicrowaveEndpoint::MicrowaveEndpoint(Pistache::Address addr)
    : httpEndpoint(std::make_shared<Pistache::Http::Endpoint>(addr))
{
}

void MicrowaveEndpoint::init(size_t thr)
{
    auto opts = Http::Endpoint::options()
                    .threads(static_cast<int>(thr));
    httpEndpoint->init(opts);
    setupRoutes();
}

void MicrowaveEndpoint::startThreaded()
{
    httpEndpoint->setHandler(router.handler());
    httpEndpoint->serveThreaded();
}

void MicrowaveEndpoint::stop()
{
    httpEndpoint->shutdown();
}

void MicrowaveEndpoint::setupRoutes()
{
    Rest::Routes::Get(router, "/auth", Rest::Routes::bind(&MicrowaveEndpoint::doAuth, this));
    Rest::Routes::Post(router, "/settings/:settingName/:value", Rest::Routes::bind(&MicrowaveEndpoint::setSetting, this));
    Rest::Routes::Get(router, "/settings/:settingName/", Rest::Routes::bind(&MicrowaveEndpoint::getSetting, this));
}

void MicrowaveEndpoint::doAuth(const Rest::Request &request, Http::ResponseWriter response)
{
    response.send(Http::Code::Ok, "1");
}

void MicrowaveEndpoint::setSetting(const Rest::Request &request, Http::ResponseWriter response)
{
    auto settingName = request.param(":settingName").as<std::string>();
    Guard guard(microwaveLock);

    std::string val = "";

    if (request.hasParam(":value"))
    {
        auto value = request.param(":value");
        val = value.as<std::string>();
    }

    int setResponse = mwv.set(settingName, val);

    if (setResponse == 1)
    {
        response.send(Http::Code::Ok, settingName + " was set to " + val);
    }
    else
    {
        response.send(Http::Code::Not_Found, settingName + " was not found and or '" + val + "' was not a valid value ");
    }
}

// Setting to get the settings value of one of the configurations of the Microwave
void MicrowaveEndpoint::getSetting(const Rest::Request &request, Http::ResponseWriter response)
{
    auto settingName = request.param(":settingName").as<std::string>();
    Guard guard(microwaveLock);

    std::string valueSetting = mwv.get(settingName);

    if (valueSetting != "")
    {
        response.headers()
            .add<Http::Header::Server>("pistache/0.1")
            .add<Http::Header::ContentType>(MIME(Text, Plain));
        response.send(Http::Code::Ok, settingName + " is " + valueSetting);
    }
    else
    {
        response.send(Http::Code::Not_Found, settingName + " was not found");
    }
}