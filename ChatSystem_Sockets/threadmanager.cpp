#include "threadmanager.h"
#include <QDebug>

ThreadManager& ThreadManager::instance()
{
    static ThreadManager instance;
    return instance;
}

ThreadManager::ThreadManager(QObject* parent) : QObject(parent)
{
}

ThreadManager::~ThreadManager()
{
    stopAllThreads();
}

void ThreadManager::startClientThread(Client* client)
{
    QMutexLocker locker(&mutex);

    QThread* thread = new QThread();
    client->moveToThread(thread);

    connect(thread, &QThread::started, client, &Client::run);
    connect(client, &Client::finished, thread, &QThread::quit);
    connect(client, &Client::finished, client, &Client::deleteLater);
    connect(thread, &QThread::finished, thread, &QThread::deleteLater);

    threads.append(thread);
    clients.append(client);

    thread->start();

    emit threadStarted(client->getClientInfo());
}

void ThreadManager::stopAllThreads()
{
    QMutexLocker locker(&mutex);

    for (Client* client : clients) {
        client->stop();
    }

    for (QThread* thread : threads) {
        thread->quit();
        if (!thread->wait(3000)) {
            thread->terminate();
            thread->wait();
        }
    }

    threads.clear();
    clients.clear();
}

int ThreadManager::activeThreads() const
{
    QMutexLocker locker(&mutex);
    return threads.size();
}