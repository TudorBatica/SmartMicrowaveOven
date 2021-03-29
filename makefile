main: main.cpp src/domain/Job.cpp src/domain/Preset.cpp ArgumentsParser.cpp Microwave.cpp src/presentation/MicrowaveEndpoint.cpp SignalsChecker.cpp
	g++ main.cpp src/domain/Job.cpp src/domain/Preset.cpp ArgumentsParser.cpp Microwave.cpp src/presentation/MicrowaveEndpoint.cpp SignalsChecker.cpp -o main -lpistache -lcrypto -lssl -lpthread
