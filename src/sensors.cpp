#include "sensors.hpp"

PulseSensor::PulseSensor(const QString &a_id, const QString &a_room, const QString &a_log, const QString &a_config)
    : Device(a_id, "PulseSensor", a_room, a_log, a_config), m_gen(m_rd()), m_dist(60, 100) {}

int PulseSensor::generate_pulse_reading()
{
    return m_dist(m_gen);
}

void PulseSensor::monitor_pulse()
{
    int pulse = generate_pulse_reading();
    PulseEvent* event = new PulseEvent(QDateTime::currentDateTime(), QString::number(pulse), m_room);
    publish_event(event);
}


BloodPressureCuff::BloodPressureCuff(const QString &a_id, const QString &a_room, const QString &a_log, const QString &a_config)
    : Device(a_id, "BloodPressureCuff", a_room, a_log, a_config), m_gen(m_rd()), m_systolic_dist(110, 140), m_diastolic_dist(60, 90) {}

std::pair<int, int> BloodPressureCuff::generate_pressure_reading()
{
    return {m_systolic_dist(m_gen), m_diastolic_dist(m_gen)};
}

void BloodPressureCuff::monitor_pressure()
{
    auto pressure = generate_pressure_reading();
    QString data = QString::number(pressure.first) + "/" + QString::number(pressure.second);
    PressureEvent* event = new PressureEvent(QDateTime::currentDateTime(), data, m_room);
    publish_event(event);
}


Oximeter::Oximeter(const QString &a_id, const QString &a_room, const QString &a_log, const QString &a_config)
    : Device(a_id, "Oximeter", a_room, a_log, a_config), m_gen(m_rd()), m_dist(94, 100) {}

int Oximeter::generate_saturation_reading()
{
    return m_dist(m_gen);
}

void Oximeter::monitor_saturation()
{
    int saturation = generate_saturation_reading();
    QString saturationData = QString("%%SpO2 %1").arg(saturation);
    SaturationEvent* event = new SaturationEvent(QDateTime::currentDateTime(), saturationData, m_room);
    publish_event(event);
}


Thermometer::Thermometer(const QString &a_id, const QString &a_room, const QString &a_log, const QString &a_config)
    : Device(a_id, "Thermometer", a_room, a_log, a_config), m_gen(m_rd()), m_dist(36.0, 37.4) {}

double Thermometer::generate_temperature_reading()
{
    return m_dist(m_gen);
}

void Thermometer::monitor_temperature()
{
    double temperature = generate_temperature_reading();
    TemperatureEvent* event = new TemperatureEvent(QDateTime::currentDateTime(), QString::number(temperature), m_room);
    publish_event(event);
}

