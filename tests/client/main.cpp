#include <QCoreApplication>
#include <QDebug>
#include "client.hpp"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    qDebug() << "Starting Client...";

    spd::Client client;  // Client object is instantiated, and its manager is automatically constructed.
    
    client.connect_to_server("127.0.0.1", 5555);

    return a.exec(); // Let the application run, waiting for events/data from the server.
}
