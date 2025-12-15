#ifndef CLIENT_H
#define CLIENT_H

#include <QObject>
#include <QString>
#include <QTcpSocket>

class Client : public QObject
{
    Q_OBJECT
public:
    explicit Client(QObject* parent = nullptr);
    void connectToServer(const QString& host, quint16 port);
    void sendMessage(const QString& message);

signals:
    void messageReceived(const QString& message);

private slots:
    void readyRead();
    void connected();

private:
    QTcpSocket* socket;
};

#endif // CLIENT_H