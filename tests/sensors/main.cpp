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

    PulseSensor sensor1("sensorID1", "1", "log1", "config1");
    sensor1.get_manager()->connect_to_server("127.0.0.1", 12345);
    QTimer timer1;
    QObject::connect(&timer1, &QTimer::timeout, [&sensor1]() {
        qDebug() << "Monitoring pulse from sensor in Room 1...";
        sensor1.monitor_pulse();
    });
    timer1.start(1000);

    return a.exec();
}
