main: main.cpp ArgumentsParser.cpp Microwave.cpp MicrowaveEndpoint.cpp SignalsChecker.cpp
	g++ main.cpp ArgumentsParser.cpp Microwave.cpp MicrowaveEndpoint.cpp SignalsChecker.cpp -o main -lpistache -lcrypto -lssl -lpthread
