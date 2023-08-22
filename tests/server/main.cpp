#include <QTcpServer>
#include <QTcpSocket>
#include <QCoreApplication>
#include <QDebug>
#include <QDataStream>
#include <QDateTime>
#include "simple_server.hpp"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    SimpleServer server;
    return a.exec();
}
