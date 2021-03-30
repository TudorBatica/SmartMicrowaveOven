#include <pistache/endpoint.h>
#include "MicrowaveEndpoint.h"
#include "../domain/Job.h"
#include "../domain/Preset.h"

using namespace Pistache;

MicrowaveEndpoint::MicrowaveEndpoint(Pistache::Address addr, service::IPresetService *presetService)
    : httpEndpoint(std::make_shared<Pistache::Http::Endpoint>(addr))
{
    this->presetService = presetService;
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
}

void MicrowaveEndpoint::getPresets(const Rest::Request &request, Http::ResponseWriter response)
{
    auto presets = presetService->getPresets();
    std::string stringPresets = "[";
    for (auto &preset : presets)
    {
        stringPresets += preset.toJson() + ",\n";
    }
    stringPresets += "]";

    response.send(Http::Code::Ok, stringPresets);
}

void MicrowaveEndpoint::addPreset(const Rest::Request &request, Http::ResponseWriter response)
{
    try
    {
        auto job = std::make_shared<domain::Job>(domain::jobTypeFromString(request.param(":jobtype").as<std::string>()),
                                                 request.param(":duration").as<int>(),
                                                 domain::powerLevelFromString(request.param(":power").as<std::string>()));
        auto preset = domain::Preset(request.param(":food").as<std::string>(), *job);
        presetService->addPreset(preset);

        response.send(Http::Code::Created, preset.toJson());
    }
    catch (const std::exception &ex)
    {
        response.send(Http::Code::Internal_Server_Error, ex.what());
    }
}
