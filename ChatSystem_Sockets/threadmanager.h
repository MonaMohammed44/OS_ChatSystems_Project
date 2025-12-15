#pragma once
#ifndef THREADMANAGER_H
#define THREADMANAGER_H

#include <QObject>
#include <QThread>
#include <QList>
#include <QMutex>
#include "client.h"

class ThreadManager : public QObject
{
    Q_OBJECT

public:
    static ThreadManager& instance();

    void startClientThread(Client* client);
    void stopAllThreads();
    int activeThreads() const;

signals:
    void threadStarted(QString threadName);
    void threadFinished(QString threadName);
    void threadError(QString error);

private:
    ThreadManager(QObject* parent = nullptr);
    ~ThreadManager();

    QList<QThread*> threads;
    QList<Client*> clients;
    mutable QMutex mutex;

    ThreadManager(const ThreadManager&) = delete;
    ThreadManager& operator=(const ThreadManager&) = delete;
};

#endif // THREADMANAGER_H