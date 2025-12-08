#include "server.h"

ChatServer::ChatServer() {
    WSAData wsData;
    WSAStartup(MAKEWORD(2, 2), &wsData);
}

bool ChatServer::startServer(int port) {
    listeningSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (listeningSocket == INVALID_SOCKET) {
        cout << "Error creating socket\n";
        return false;
    }

    sockaddr_in hint;
    hint.sin_family = AF_INET;
    hint.sin_port = htons(port);
    hint.sin_addr.s_addr = INADDR_ANY;

    if (bind(listeningSocket, (sockaddr*)&hint, sizeof(hint)) == SOCKET_ERROR) {
        cout << "Bind failed\n";
        return false;
    }

    listen(listeningSocket, SOMAXCONN);
    cout << "Server started on port " << port << "\n";
    return true;
}

void ChatServer::handleClient(SOCKET clientSocket) {
    char buffer[4096];

    while (true) {
        ZeroMemory(buffer, 4096);
        int bytes = recv(clientSocket, buffer, 4096, 0);

        if (bytes <= 0) break;

        cout << "Client: " << buffer << endl;

        send(clientSocket, buffer, bytes, 0);
    }

    closesocket(clientSocket);
}

void ChatServer::run() {
    SOCKET clientSocket;
    sockaddr_in client;
    int clientSize = sizeof(client);

    while (true) {
        clientSocket = accept(listeningSocket, (sockaddr*)&client, &clientSize);

        if (clientSocket == INVALID_SOCKET) continue;

        cout << "Client connected!\n";

        thread clientThread(&ChatServer::handleClient, this, clientSocket);
        clientThread.detach();
    }
}
