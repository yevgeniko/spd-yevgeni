#include <QCoreApplication>
#include <QTimer>
#include <QDebug>
#include <signal.h>
#include "../../inc/device.hpp"
#include "../../inc/sensors.hpp"
#include "../../inc/device_manager.hpp"



int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);


    qDebug() << "Starting application...";

    DeviceManager manager;
    
    manager.connectToServer("127.0.0.1", 12345);

    PulseSensor sensor("sensorID1", "roomA", "log1", "config1");
    sensor.setManager(&manager);
    manager.registerDevice(&sensor);

    QTimer timer;
    QObject::connect(&timer, &QTimer::timeout, [&sensor]() {
        qDebug() << "Monitoring pulse...";
        sensor.monitorPulse();
    });
    timer.start(1000);

    return a.exec();
}
