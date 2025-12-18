#include "chatmessage.h"
#include <QDateTime>
#include <QStringList>

ChatMessage::ChatMessage()
    : type(MSG_TEXT), timestamp(QDateTime::currentDateTime().toString("hh:mm:ss"))
{
}

ChatMessage::ChatMessage(const QString& sender, const QString& content,
    MessageType type)
    : sender(sender), content(content), type(type),
    timestamp(QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss"))
{
}

void ChatMessage::setSender(const QString& sender)
{
    if (this->sender != sender) {
        this->sender = sender;
    }
}

void ChatMessage::setContent(const QString& content)
{
    if (this->content != content) {
        this->content = content;
    }
}

void ChatMessage::setType(MessageType type)
{
    if (this->type != type) {
        this->type = type;
    }
}

void ChatMessage::setReceiver(const QString& receiver)
{
    if (this->receiver != receiver) {
        this->receiver = receiver;
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

QString ChatMessage::serialize() const
{
    // Keep protocol compatible with the previous wire format:
    // type|sender|content|timestamp|receiver
    return QString("%1|%2|%3|%4|%5")
        .arg(static_cast<int>(type))
        .arg(sender)
        .arg(content)
        .arg(timestamp)
        .arg(receiver);
}

ChatMessage ChatMessage::fromNetwork(const QString& data)
{
    return ChatMessage::deserialize(data);
}

ChatMessage ChatMessage::deserialize(const QString& data)
{
    QStringList parts = data.split("|");
    ChatMessage msg;
    if (parts.size() >= 5) {
        msg.type = static_cast<MessageType>(parts[0].toInt());
        msg.sender = parts[1];
        msg.content = parts[2];
        msg.timestamp = parts[3];
        msg.receiver = parts[4];
    }
    return msg;
}

QString ChatMessage::formatTimestamp(const QDateTime& dt)
{
    return dt.toString("yyyy-MM-dd hh:mm:ss");
}