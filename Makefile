APP = simpleHttpServer.cpp

default:
	g++ -I/home/darius/dev/uWebSocketsProjects/uWebSockets/src -I/home/darius/dev/uWebSocketsProjects/uWebSockets/uSockets/src $(APP) /home/darius/dev/uWebSocketsProjects/uWebSockets/uSockets/uSockets.a -lz
