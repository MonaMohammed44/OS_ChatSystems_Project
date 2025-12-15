#include "gui.h"
#include <QApplication>

GUI::GUI(QWidget* parent) : QWidget(parent)
{
    chatDisplay = new QTextEdit(this);
    chatDisplay->setReadOnly(true);

    messageInput = new QLineEdit(this);
    sendButton = new QPushButton("Send", this);

    QHBoxLayout* inputLayout = new QHBoxLayout;
    inputLayout->addWidget(messageInput);
    inputLayout->addWidget(sendButton);

    QVBoxLayout* mainLayout = new QVBoxLayout;
    mainLayout->addWidget(chatDisplay);
    mainLayout->addLayout(inputLayout);

    setLayout(mainLayout);
    setWindowTitle("Socket Chat System");

    client = new Client(this);
    client->connectToServer("127.0.0.1", 1234);

    connect(sendButton, &QPushButton::clicked, this, &GUI::sendMessage);
    connect(client, &Client::messageReceived, this, &GUI::displayMessage);
}

void GUI::sendMessage()
{
    QString message = messageInput->text();
    if (!message.isEmpty()) {
        client->sendMessage(message);
        chatDisplay->append("You: " + message);
        messageInput->clear();
    }
}

void GUI::displayMessage(const QString& message)
{
    chatDisplay->append("Other: " + message);
}