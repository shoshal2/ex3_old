a.out: MainFlow.o LuxuryCab.o TaxiCenter.o StandardCab.o bfs.o Grid.o GridPoint.o Point.o Driver.o Trip.o Passenger.o Obstacle.o TaxiCab.o
	g++ -g -Wall -std=c++0x MainFlow.o LuxuryCab.o TaxiCenter.o StandardCab.o bfs.o Grid.o GridPoint.o Point.o Driver.o Trip.o Passenger.o Obstacle.o TaxiCab.o

Passenger.o: Passenger.cpp Passenger.h
	g++ -g -Wall -c -std=c++0x Passenger.cpp

Driver.o: Driver.cpp Driver.h
	g++ -g -Wall -c -std=c++0x Driver.cpp

GridPoint.o: GridPoint.cpp GridPoint.h
	g++ -g -Wall -c -std=c++0x GridPoint.cpp

LuxuryCab.o: LuxuryCab.cpp LuxuryCab.h
	g++ -g -Wall -c -std=c++0x LuxuryCab.cpp

StandardCab.o: StandardCab.cpp StandardCab.h
	g++ -g -Wall -c -std=c++0x StandardCab.cpp

TaxiCenter.o: TaxiCenter.cpp TaxiCenter.h
	g++ -g -Wall -c -std=c++0x TaxiCenter.cpp

Trip.o: Trip.cpp Trip.h
	g++ -g -Wall -c -std=c++0x Trip.cpp

Grid.o: Grid.cpp Grid.h
	g++ -g -Wall -c -std=c++0x Grid.cpp

TaxiCab.o: TaxiCab.cpp TaxiCab.h
	g++ -g -Wall -c -std=c++0x TaxiCab.cpp

Point.o: Point.cpp Point.h
	g++ -g -Wall -c -std=c++0x Point.cpp

bfs.o: bfs.cpp bfs.h
	g++ -g -Wall -c -std=c++0x bfs.cpp

Obstacle.o: Obstacle.cpp Obstacle.h
	g++ -g -Wall -c -std=c++0x Obstacle.cpp

MainFlow.o: MainFlow.cpp
	g++ -g -Wall -c -std=c++0x MainFlow.cpp
