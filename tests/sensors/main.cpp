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

    qDebug() << "Starting Sensor...";

    PulseSensor sensor("sensorID1", "roomA", "log1", "config1");
    
    sensor.getManager()->connectToServer("127.0.0.1", 12345);

    QTimer timer;
    QObject::connect(&timer, &QTimer::timeout, [&sensor]() {
        qDebug() << "Monitoring pulse...";
        sensor.monitorPulse();
    });
    timer.start(1000);

    return a.exec();
}