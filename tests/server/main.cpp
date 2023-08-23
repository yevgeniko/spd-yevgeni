#include <QTcpServer>
#include <QTcpSocket>
#include <QCoreApplication>
#include <QDebug>
#include <QDataStream>
#include <QDateTime>
#include "server_manager.hpp"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    ServerManager manager;
    manager.start_services(); // loading the MAIN SERVER MANAGER
    return a.exec();
}
