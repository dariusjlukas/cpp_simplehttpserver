APP = simpleHttpServer.cpp
UWEBSOCKETS_DIR ?= /your/uWebsockets/directory

default:
	g++ -I${UWEBSOCKETS_DIR}/src -I${UWEBSOCKETS_DIR}/uSockets/src $(APP) ${UWEBSOCKETS_DIR}/uSockets/uSockets.a -lz
