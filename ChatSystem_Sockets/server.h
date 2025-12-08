
#pragma once
#include <winsock2.h>
#include <ws2tcpip.h>
#include <iostream>
#include <thread>
using namespace std;

class ChatServer {
private:
    SOCKET listeningSocket;

public:
    ChatServer();
    bool startServer(int port);
    void handleClient(SOCKET clientSocket);
    void run();
};
