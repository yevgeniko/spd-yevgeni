#ifndef SENSORS_HPP
#define SENSORS_HPP

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

class BloodPressureCuff : public Device
{
public:
    BloodPressureCuff(const QString &a_id, const QString &a_room, const QString &a_log, const QString &a_config);
    std::pair<int, int> generate_pressure_reading(); 
    void monitor_pressure(); 

private:
    std::random_device m_rd;
    std::mt19937 m_gen;
    std::uniform_int_distribution<> m_systolic_dist;
    std::uniform_int_distribution<> m_diastolic_dist;
};

class Oximeter : public Device
{
public:
    Oximeter(const QString &a_id, const QString &a_room, const QString &a_log, const QString &a_config);
    int generate_saturation_reading();
    void monitor_saturation();

private:
    std::random_device m_rd;
    std::mt19937 m_gen;
    std::uniform_int_distribution<> m_dist;
};

class Thermometer : public Device
{
public:
    Thermometer(const QString &a_id, const QString &a_room, const QString &a_log, const QString &a_config);
    double generate_temperature_reading();
    void monitor_temperature();

private:
    std::random_device m_rd;
    std::mt19937 m_gen;
    std::uniform_real_distribution<> m_dist;
};


#endif // SENSORS
