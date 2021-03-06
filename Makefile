program: main.o Bak.o Relay.o AutomaatApi.o Screen.o HTTP.o StepperMotor.o KeyPad.o Trunk.o
	g++ -o main main.o Bak.o Relay.o AutomaatApi.o Screen.o HTTP.o StepperMotor.o KeyPad.o Trunk.o -std=c++11 -lwiringPi -lwiringPiDev -lcurl -pthread

main.o: main.cpp
	g++ -c main.cpp -std=c++11

Relay.o: Relay.cpp Relay.h
	g++ -c Relay.cpp

Screen.o: Screen.cpp Screen.h
	g++ -c Screen.cpp

HTTP.o: HTTP.cpp HTTP.h
	g++ -c HTTP.cpp -std=c++11

Bak.o: Bak.cpp Bak.h
	g++ -c Bak.cpp -std=c++11

AutomaatApi.o: AutomaatApi.cpp AutomaatApi.h
	g++ -c AutomaatApi.cpp -std=c++11

StepperMotor.o: StepperMotor.cpp StepperMotor.h
	g++ -c StepperMotor.cpp

Trunk.o: Trunk.cpp Trunk.h
		g++ -c Trunk.cpp

KeyPad.o: KeyPad.cpp KeyPad.h
	g++ -c KeyPad.cpp -std=c++11

clean:
	rm -f *.o main
