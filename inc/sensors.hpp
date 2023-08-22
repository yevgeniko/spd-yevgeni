#ifndef PULSESENSOR_HPP
#define PULSESENSOR_HPP

#include "device.hpp"
#include <random>

class PulseSensor : public Device
{
    std::random_device rd;
    std::mt19937 gen;
    std::uniform_int_distribution<> dist;

public:
    PulseSensor(const QString &id, const QString &room, const QString &log, const QString &config);
    int generatePulseReading();

        void monitorPulse() {
        int pulse = generatePulseReading();
        PulseEvent* event = new PulseEvent(QString::number(pulse), room);
        publishEvent(event);
    }
};

#endif // PULSESENSOR_HPP
