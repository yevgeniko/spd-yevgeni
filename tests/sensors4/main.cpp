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

    Thermometer sensor4("sensorID4", "4", "log4", "config4");
    sensor4.get_manager()->connect_to_server("127.0.0.1", 12345);
    QTimer timer4;
    QObject::connect(&timer4, &QTimer::timeout, [&sensor4]() {
        qDebug() << "Monitoring temperature from sensor in Room 4...";
        sensor4.monitor_temperature();
    });
    timer4.start(4000);

    return a.exec();
}
