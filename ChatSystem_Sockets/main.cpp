#include <QApplication>
#include "gui.h"
#include "server.h"
#include <QMessageBox>
#include <QCommandLineParser>
#include <QCommandLineOption>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    try {
        QCommandLineParser parser;
        parser.setApplicationDescription("Socket Chat System - OS Project");
        parser.addHelpOption();

        QCommandLineOption serverModeOpt(QStringList() << "s" << "server",
                                         "Run in server mode (start listening).");
        QCommandLineOption hostOpt(QStringList() << "H" << "host",
                                   "Server host/IP to connect to (client mode).",
                                   "host",
                                   "127.0.0.1");
        QCommandLineOption portOpt(QStringList() << "p" << "port",
                                   "Server port.",
                                   "port",
                                   "1234");

        parser.addOption(serverModeOpt);
        parser.addOption(hostOpt);
        parser.addOption(portOpt);
        parser.process(app);

        const bool serverMode = parser.isSet(serverModeOpt);
        const QString host = parser.value(hostOpt);
        const quint16 port = static_cast<quint16>(parser.value(portOpt).toUShort());

        // Start server only when requested
        Server server;
        if (serverMode) {
            if (!server.startServer(port)) {
                QMessageBox::critical(nullptr, "Error", "Failed to start server!");
                return 1;
            }
        }

        // Start GUI
        GUI chatWindow(host, port);
        chatWindow.setWindowTitle("Socket Chat System - OS Project");
        chatWindow.show();

        return app.exec();
    }
    catch (const std::exception& e) {
        QMessageBox::critical(nullptr, "Error", QString("Exception: %1").arg(e.what()));
        return 1;
    }
}
