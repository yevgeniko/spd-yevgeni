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

    // First sensor for Room 1
    PulseSensor sensor1("sensorID1", "1", "log1", "config1");
    sensor1.get_manager()->connect_to_server("127.0.0.1", 12345);
    QTimer timer1;
    QObject::connect(&timer1, &QTimer::timeout, [&sensor1]() {
        qDebug() << "Monitoring pulse from sensor in Room 1...";
        sensor1.monitor_pulse();
    });
    timer1.start(1000);

    QThread::sleep(1);

    // Second sensor for Room 2
    PulseSensor sensor2("sensorID2", "2", "log2", "config2");
    sensor2.get_manager()->connect_to_server("127.0.0.1", 12345);
    QTimer timer2;
    QObject::connect(&timer2, &QTimer::timeout, [&sensor2]() {
        qDebug() << "Monitoring pulse from sensor in Room 2...";
        sensor2.monitor_pulse();
    });
    timer2.start(1000);

    QThread::sleep(1);

    // Third sensor for Room 3
    PulseSensor sensor3("sensorID3", "3", "log3", "config3");
    sensor3.get_manager()->connect_to_server("127.0.0.1", 12345);
    QTimer timer3;
    QObject::connect(&timer3, &QTimer::timeout, [&sensor3]() {
        qDebug() << "Monitoring pulse from sensor in Room 3...";
        sensor3.monitor_pulse();
    });
    timer3.start(1000);

    return a.exec();
}