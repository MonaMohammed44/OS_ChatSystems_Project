#pragma once
#ifndef CHATMESSAGE_H
#define CHATMESSAGE_H

#include <QString>
#include <QDateTime>
#include <QMetaType>
#include "protocol.h"

class ChatMessage : public QObject
{
    Q_OBJECT

public:
    ChatMessage(QObject* parent = nullptr);
    ChatMessage(const QString& sender, const QString& content,
        MessageType type = MSG_TEXT, QObject* parent = nullptr);

    // Getters
    QString getSender() const { return sender; }
    QString getContent() const { return content; }
    QString getTimestamp() const { return timestamp; }
    MessageType getType() const { return type; }
    QString getReceiver() const { return receiver; }

    // Setters
    void setSender(const QString& sender);
    void setContent(const QString& content);
    void setType(MessageType type);
    void setReceiver(const QString& receiver);

    // Formatting
    QString toString() const;
    QString toHtml() const;
    QString toNetworkFormat() const;

    // Static methods
    static ChatMessage fromNetwork(const QString& data);
    static QString formatTimestamp(const QDateTime& dt);

signals:
    void messageChanged();

private:
    QString sender;
    QString content;
    QString timestamp;
    MessageType type;
    QString receiver;
};

// Register for Qt's meta-object system
Q_DECLARE_METATYPE(ChatMessage)

#endif // CHATMESSAGE_H