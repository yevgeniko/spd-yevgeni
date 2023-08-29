#include "sensors.hpp"

PulseSensor::PulseSensor(const QString &a_id, const QString &a_room, const QString &a_log, const QString &a_config)
    : Device(a_id, "PulseSensor", a_room, a_log, a_config), m_gen(m_rd()), m_dist(80, 120) {}

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
