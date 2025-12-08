#include "client.h"

ChatClient::ChatClient() {
    WSAData wsData;
    WSAStartup(MAKEWORD(2, 2), &wsData);
}

bool ChatClient::connectToServer(string ip, int port) {
    clientSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (clientSocket == INVALID_SOCKET) {
        cout << "Error creating socket\n";
        return false;
    }

    sockaddr_in hint;
    hint.sin_family = AF_INET;
    hint.sin_port = htons(port);
    inet_pton(AF_INET, ip.c_str(), &hint.sin_addr);

    if (connect(clientSocket, (sockaddr*)&hint, sizeof(hint)) == SOCKET_ERROR) {
        cout << "Could not connect to server\n";
        return false;
    }

    cout << "Connected to server!\n";
    return true;
}

void ChatClient::sendMessage(string msg) {
    send(clientSocket, msg.c_str(), msg.size() + 1, 0);
}

void ChatClient::receiveMessages() {
    char buffer[4096];

    while (true) {
        ZeroMemory(buffer, 4096);
        int bytes = recv(clientSocket, buffer, 4096, 0);

        if (bytes > 0) {
            cout << "Server: " << buffer << endl;
        }
    }
}
