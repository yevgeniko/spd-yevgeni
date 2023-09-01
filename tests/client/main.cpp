#include <QApplication>
#include <QDebug>
#include "client.hpp"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    qDebug() << "Starting Client...";

    spd::Client client;
    
    client.connect_to_server(QHostAddress::LocalHost, 5555);

    return a.exec();
}
