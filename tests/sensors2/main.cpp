#include <QCoreApplication>
#include <QTimer>
#include <QDebug>
#include <signal.h>
#include "device.hpp"
#include "sensors.hpp"
#include "device_manager.hpp"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    qDebug() << "Starting Sensors...";

    BloodPressureCuff sensor2("sensorID2", "2", "log2", "config2");
    sensor2.get_manager()->connect_to_server("127.0.0.1", 12345);
    QTimer timer2;
    QObject::connect(&timer2, &QTimer::timeout, [&sensor2]() {
        qDebug() << "Monitoring blood pressure from sensor in Room 2...";
        sensor2.monitor_pressure();
    });
    timer2.start(2000);

    return a.exec();
}
