#include <QApplication>
#include <QDebug>
#include "client.hpp"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    qDebug() << "Starting Client...";

    spd::Client client;
    
    //client.connect_to_server("127.0.0.1", 5555);

    return a.exec();
}
