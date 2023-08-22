#include "sensors.hpp"

PulseSensor::PulseSensor(const QString &id, const QString &room, const QString &log, const QString &config)
    : Device(id, "PulseSensor", room, log, config), gen(rd()), dist(60, 100) {}

int PulseSensor::generatePulseReading()
{
    return dist(gen);
}
