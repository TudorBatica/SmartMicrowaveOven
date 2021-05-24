main: src/domain/PowerLevel.cpp src/domain/JobType.cpp src/main.cpp src/service/PresetService.cpp src/infrastructure/PresetRepository.cpp src/domain/Job.cpp src/domain/Preset.cpp src/startup/ArgumentsParser.cpp src/presentation/MicrowaveEndpoint.cpp src/startup/SignalsChecker.cpp src/domain/Command.cpp src/infrastructure/CommandRepository.cpp src/service/CommandService.cpp
	g++ -std=c++17 src/domain/PowerLevel.cpp src/domain/JobType.cpp src/main.cpp src/service/PresetService.cpp src/infrastructure/PresetRepository.cpp src/domain/Job.cpp src/domain/Preset.cpp src/startup/ArgumentsParser.cpp src/presentation/MicrowaveEndpoint.cpp src/startup/SignalsChecker.cpp src/domain/Command.cpp src/infrastructure/CommandRepository.cpp src/service/CommandService.cpp -o main -lpistache -lcrypto -lssl -lpthread
