// pulsesensor.hpp
#ifndef PULSESENSOR_HPP
#define PULSESENSOR_HPP

#include "device.hpp"
#include <random>
#include <QString>

class PulseSensor : public Device
{

public:
    PulseSensor(const QString &a_id, const QString &a_room, const QString &a_log, const QString &a_config);
    int generate_pulse_reading();
    void monitor_pulse();

private:
    std::random_device m_rd;
    std::mt19937 m_gen;
    std::uniform_int_distribution<> m_dist;
};

#endif // PULSESENSOR_HPP
