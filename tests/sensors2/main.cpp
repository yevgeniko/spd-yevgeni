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

    PulseSensor sensor1("sensorID1", "2", "log1", "config1");
    sensor1.get_manager()->connect_to_server("127.0.0.1", 12345);
    QTimer timer1;
    QObject::connect(&timer1, &QTimer::timeout, [&sensor1]() {
        qDebug() << "Monitoring pulse from sensor in Room 2...";
        sensor1.monitor_pulse();
    });
    timer1.start(15000);

    Oximeter sensor3("sensorID3", "2", "log3", "config3");
    sensor3.get_manager()->connect_to_server("127.0.0.1", 12345);
    QTimer timer3;
    QObject::connect(&timer3, &QTimer::timeout, [&sensor3]() {
        qDebug() << "Monitoring SpO2 from sensor in Room 2...";
        sensor3.monitor_saturation();
    });
    timer3.start(15500);

    BloodPressureCuff sensor2("sensorID2", "2", "log2", "config2");
    sensor2.get_manager()->connect_to_server("127.0.0.1", 12345);
    QTimer timer2;
    QObject::connect(&timer2, &QTimer::timeout, [&sensor2]() {
        qDebug() << "Monitoring blood pressure from sensor in Room 2...";
        sensor2.monitor_pressure();
    });
    timer2.start(16000);

    Thermometer sensor4("sensorID4", "2", "log4", "config4");
    sensor4.get_manager()->connect_to_server("127.0.0.1", 12345);
    QTimer timer4;
    QObject::connect(&timer4, &QTimer::timeout, [&sensor4]() {
        qDebug() << "Monitoring temperature from sensor in Room 2...";
        sensor4.monitor_temperature();
    });
    timer4.start(16500);


    return a.exec();
}
