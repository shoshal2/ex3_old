all:

	g++  MainFlow.cpp Socket.cpp Tcp.cpp bfs.cpp Driver.cpp Trip.cpp Grid.cpp GridPoint.cpp LuxuryCab.cpp StandardCab.cpp TaxiCab.cpp Obstacle.cpp Passenger.cpp Point.cpp TaxiCenter.cpp -o s -lpthread -lboost_serialization

	g++ client.cpp Socket.cpp Tcp.cpp bfs.cpp Driver.cpp Trip.cpp Grid.cpp GridPoint.cpp LuxuryCab.cpp StandardCab.cpp TaxiCab.cpp Obstacle.cpp Passenger.cpp Point.cpp TaxiCenter.cpp -o c -lpthread -lboost_serialization

