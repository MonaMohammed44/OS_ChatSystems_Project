#include "server.h"
#include <QDebug>

Server::Server(QObject* parent) : QTcpServer(parent) {}

bool Server::startServer()
{
    if (!listen(QHostAddress::Any, 1234)) {
        qDebug() << "Server could not start!";
        return false;
    }
    else {
        qDebug() << "Server started on port 1234";
        return true;
    }
}

void Server::incomingConnection(qintptr socketDescriptor)
{
    QTcpSocket* client = new QTcpSocket(this);
    client->setSocketDescriptor(socketDescriptor);
    clients.append(client);

    connect(client, &QTcpSocket::readyRead, this, &Server::readyRead);
    connect(client, &QTcpSocket::disconnected, this, &Server::disconnected);

    qDebug() << "New client connected.";
}

void Server::readyRead()
{
    QTcpSocket* client = qobject_cast<QTcpSocket*>(sender());
    QByteArray data = client->readAll();
    QString message = QString::fromUtf8(data);

    qDebug() << "Message from client:" << message;

    // Broadcast to all clients
    for (QTcpSocket* otherClient : clients) {
        if (otherClient != client) {
            otherClient->write(data);
        }
    }
}

void Server::disconnected()
{
    QTcpSocket* client = qobject_cast<QTcpSocket*>(sender());
    clients.removeAll(client);
    client->deleteLater();
    qDebug() << "Client disconnected.";
}