all:

	g++  *clientFiles/*.cpp *clientFiles/*.h -lm -ansi -pedantic -lboost_serialization -o client.out

	g++  *serverFiles/*.cpp *serverFiles/*.h -lm -ansi -pedantic -lboost_serialization -o server.out
