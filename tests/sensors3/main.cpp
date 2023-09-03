#include <QCoreApplication>
#include <QTimer>
#include <QDebug>
#include <QThread>
#include <signal.h>
#include "device.hpp"
#include "sensors.hpp"
#include "device_manager.hpp"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    qDebug() << "Starting Sensors...";

    Oximeter sensor3("sensorID3", "3", "log3", "config3");
    sensor3.get_manager()->connect_to_server("127.0.0.1", 12345);
    QTimer timer3;
    QObject::connect(&timer3, &QTimer::timeout, [&sensor3]() {
        qDebug() << "Monitoring SpO2 from sensor in Room 3...";
        sensor3.monitor_saturation();
    });
    timer3.start(3000);

    return a.exec();
}
