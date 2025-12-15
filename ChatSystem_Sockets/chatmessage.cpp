#include "chatmessage.h"
#include <QDateTime>

ChatMessage::ChatMessage(QObject* parent)
    : QObject(parent), type(MSG_TEXT), timestamp(QDateTime::currentDateTime().toString("hh:mm:ss"))
{
}

ChatMessage::ChatMessage(const QString& sender, const QString& content,
    MessageType type, QObject* parent)
    : QObject(parent), sender(sender), content(content), type(type),
    timestamp(QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss"))
{
}

void ChatMessage::setSender(const QString& sender)
{
    if (this->sender != sender) {
        this->sender = sender;
        emit messageChanged();
    }
}

void ChatMessage::setContent(const QString& content)
{
    if (this->content != content) {
        this->content = content;
        emit messageChanged();
    }
}

void ChatMessage::setType(MessageType type)
{
    if (this->type != type) {
        this->type = type;
        emit messageChanged();
    }
}

void ChatMessage::setReceiver(const QString& receiver)
{
    if (this->receiver != receiver) {
        this->receiver = receiver;
        emit messageChanged();
    }
}

QString ChatMessage::toString() const
{
    QString prefix;
    switch (type) {
    case MSG_SYSTEM: prefix = "[SYSTEM] "; break;
    case MSG_ERROR: prefix = "[ERROR] "; break;
    case MSG_SUCCESS: prefix = "[SUCCESS] "; break;
    default: prefix = "";
    }

    return QString("[%1] %2%3: %4")
        .arg(timestamp)
        .arg(prefix)
        .arg(sender)
        .arg(content);
}

QString ChatMessage::toHtml() const
{
    QString color;
    QString style;

    switch (type) {
    case MSG_SYSTEM:
        color = "blue";
        style = "font-weight: bold;";
        break;
    case MSG_ERROR:
        color = "red";
        style = "font-weight: bold;";
        break;
    case MSG_SUCCESS:
        color = "green";
        style = "font-weight: bold;";
        break;
    case MSG_TEXT:
        color = "black";
        style = "";
        break;
    default:
        color = "gray";
        style = "font-style: italic;";
    }

    return QString("<span style='color: %1; %2'>[%3] %4: %5</span><br>")
        .arg(color)
        .arg(style)
        .arg(timestamp)
        .arg(sender.isEmpty() ? "System" : sender)
        .arg(content.toHtmlEscaped());
}

QString ChatMessage::toNetworkFormat() const
{
    return serialize();
}

ChatMessage ChatMessage::fromNetwork(const QString& data)
{
    return ChatMessage::deserialize(data);
}

QString ChatMessage::formatTimestamp(const QDateTime& dt)
{
    return dt.toString("yyyy-MM-dd hh:mm:ss");
}