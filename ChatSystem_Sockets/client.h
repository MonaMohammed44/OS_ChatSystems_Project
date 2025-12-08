
#pragma once
#include <winsock2.h>
#include <ws2tcpip.h>
#include <iostream>
#include <string>
using namespace std;

class ChatClient {
private:
    SOCKET clientSocket;

public:
    ChatClient();
    bool connectToServer(string ip, int port);
    void sendMessage(string msg);
    void receiveMessages();
};
