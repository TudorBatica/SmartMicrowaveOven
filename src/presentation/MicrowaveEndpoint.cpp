#include <pistache/endpoint.h>
#include "MicrowaveEndpoint.h"
#include "../domain/Job.h"
#include "../domain/Preset.h"
#include "../domain/Command.h"

using namespace Pistache;

MicrowaveEndpoint::MicrowaveEndpoint(Pistache::Address addr, domain::IPresetService *presetService, domain::ICommandService *commandService, domain::IJobGeneratorService *jobGeneratorService)
    : httpEndpoint(std::make_shared<Pistache::Http::Endpoint>(addr))
{
    this->presetService = presetService;
    this->commandService = commandService;
    this->jobGeneratorService = jobGeneratorService;
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
    Rest::Routes::Get(router, "/commands", Rest::Routes::bind(&MicrowaveEndpoint::getCommands, this));
    Rest::Routes::Post(router, "/commands/:time/:presetId", Rest::Routes::bind(&MicrowaveEndpoint::addCommand, this));
    Rest::Routes::Get(router, "/generateJob/:food/:jobType/:weight", Rest::Routes::bind(&MicrowaveEndpoint::generateJob, this));
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

void MicrowaveEndpoint::getCommands(const Rest::Request &request, Http::ResponseWriter response)
{
    auto commands = commandService->getCommands();
    std::string stringCommands = "[";
    for (auto &command : commands)
    {
        stringCommands += command.toJson() + ",\n";
    }
    stringCommands += "]";

    response.send(Http::Code::Ok, stringCommands);
}

void MicrowaveEndpoint::addCommand(const Rest::Request &request, Http::ResponseWriter response)
{
    try
    {
        
        domain::Preset *p = new domain::Preset();
        *p = domain::Preset(presetService->getPresetById(request.param(":presetId").as<int>()));
        auto preset = p;                                        
        auto command = domain::Command(request.param(":time").as<std::string>(), *preset);
        commandService->addCommand(command);

        response.send(Http::Code::Created, command.toJson());
    }
    catch (const std::exception &ex)
    {
        response.send(Http::Code::Internal_Server_Error, ex.what());
    }
}

void MicrowaveEndpoint::generateJob(const Pistache::Rest::Request &request, Pistache::Http::ResponseWriter response)
{
    try
    {
        auto jobType = domain::jobTypeFromString(request.param(":jobType").as<std::string>());
        std::string food = request.param(":food").as<std::string>();
        int weight = request.param(":weight").as<int>();

        auto job = jobGeneratorService->GenerateJob(jobType, weight, food, presetService);

        response.send(Http::Code::Ok, job.toJson());
    }
    catch(const std::exception &ex)
    {
        response.send(Http::Code::Internal_Server_Error, ex.what());
    }
    
}