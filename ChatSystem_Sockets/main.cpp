#include <QApplication>
#include "gui.h"
#include "server.h"
#include <QMessageBox>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    try {
        // Start server
        Server server;
        if (!server.startServer()) {
            QMessageBox::critical(nullptr, "Error", "Failed to start server!");
            return 1;
        }

        // Start GUI
        GUI chatWindow;
        chatWindow.setWindowTitle("Socket Chat System - OS Project");
        chatWindow.show();

        return app.exec();
    }
    catch (const std::exception& e) {
        QMessageBox::critical(nullptr, "Error", QString("Exception: %1").arg(e.what()));
        return 1;
    }
}
