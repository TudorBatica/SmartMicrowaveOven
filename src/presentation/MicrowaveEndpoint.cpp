#include <pistache/endpoint.h>
#include "MicrowaveEndpoint.h"
#include "../domain/Job.h"
#include "../domain/Preset.h"

using namespace Pistache;

MicrowaveEndpoint::MicrowaveEndpoint(Pistache::Address addr, Infrastructure::IPresetRepository *presetRepository)
    : httpEndpoint(std::make_shared<Pistache::Http::Endpoint>(addr))
{
    this->presetRepository = presetRepository;
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
    Rest::Routes::Get(router, "/presets", Rest::Routes::bind(&MicrowaveEndpoint::getPresets, this));
    Rest::Routes::Post(router, "/presets/:jobtype/:food/:duration/:power", Rest::Routes::bind(&MicrowaveEndpoint::addPreset, this));
    Rest::Routes::Get(router, "/auth", Rest::Routes::bind(&MicrowaveEndpoint::doAuth, this));
    Rest::Routes::Post(router, "/settings/:settingName/:value", Rest::Routes::bind(&MicrowaveEndpoint::setSetting, this));
    Rest::Routes::Get(router, "/settings/:settingName/", Rest::Routes::bind(&MicrowaveEndpoint::getSetting, this));
}

void MicrowaveEndpoint::getPresets(const Rest::Request &request, Http::ResponseWriter response)
{
    auto presets = presetRepository->findAll();
    std::string stringPresets = "";
    for (auto &preset : presets)
    {
        stringPresets += preset.toString();
    }

    response.send(Http::Code::Ok, stringPresets);
}

void MicrowaveEndpoint::addPreset(const Rest::Request &request, Http::ResponseWriter response)
{
    try
    {
        //TODO: clean shitty object mapping
        auto food = request.param(":food").as<std::string>();
        auto duration = request.param(":duration").as<int>();
        auto job = std::make_shared<domain::Job>(domain::JobType::WARM, duration, domain::PowerLevel::HIGH);
        auto preset = std::make_shared<domain::Preset>(food, *job);

        presetRepository->add(*preset);

        response.send(Http::Code::Created, preset->toString());
    }
    catch (...)
    {
        response.send(Http::Code::Internal_Server_Error);
    }
}

void MicrowaveEndpoint::doAuth(const Rest::Request &request, Http::ResponseWriter response)
{
    response.send(Http::Code::Ok, "\n1\n");
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