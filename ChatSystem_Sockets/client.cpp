#include "client.h"
#include <QDebug>

Client::Client(QObject* parent) : QObject(parent)
{
    socket = new QTcpSocket(this);
    connect(socket, &QTcpSocket::readyRead, this, &Client::readyRead);
    connect(socket, &QTcpSocket::connected, this, &Client::connected);
}

void Client::connectToServer(const QString& host, quint16 port)
{
    socket->connectToHost(host, port);
}

void Client::sendMessage(const QString& message)
{
    if (socket->state() == QTcpSocket::ConnectedState) {
        socket->write(message.toUtf8());
    }
}

void Client::readyRead()
{
    QByteArray data = socket->readAll();
    QString message = QString::fromUtf8(data);
    emit messageReceived(message);
}

void Client::connected()
{
    qDebug() << "Connected to server.";
}