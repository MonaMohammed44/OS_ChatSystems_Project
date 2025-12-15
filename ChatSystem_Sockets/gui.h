#ifndef GUI_H
#define GUI_H

#include <QWidget>
#include <QTextEdit>
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include "client.h"

class GUI : public QWidget
{
    Q_OBJECT  // مهم جداً لـ Qt Creator

public:
    explicit GUI(QWidget *parent = nullptr);

private slots:
    void sendMessage();
    void displayMessage(const QString &message);

private:
    QTextEdit *chatDisplay;
    QLineEdit *messageInput;
    QPushButton *sendButton;
    Client *client;
};

#endif // GUI_H
