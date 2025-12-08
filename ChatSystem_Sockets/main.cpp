#include "server.h"
#include "client.h"
#include <iostream>
using namespace std;

int main() {
    int choice;
    cout << "1. Run Server\n";
    cout << "2. Run Client\n";
    cout << "Choose: ";
    cin >> choice;

    if (choice == 1) {
        ChatServer server;
        if (server.startServer(8080)) {
            server.run();
        }
    }
    else if (choice == 2) {
        ChatClient client;
        string message;

        if (client.connectToServer("127.0.0.1", 8080)) {
            thread recvThread(&ChatClient::receiveMessages, &client);
            recvThread.detach();

            while (true) {
                getline(cin >> ws, message);
                client.sendMessage(message);
            }
        }
    }

    return 0;
}
