#include "sensors.hpp"

#include <QObject>

PulseSensor::PulseSensor(const QString &a_id, const QString &a_room, const QString &a_log, const QString &a_config)
    : Device(a_id, "PulseSensor", a_room, a_log, a_config), m_gen(m_rd()), m_dist(60, 100)
{
    QTimer::singleShot(60000, this, &PulseSensor::update_distribution);
    m_timer.setInterval(10000);
    QObject::connect(&m_timer, &QTimer::timeout, this, &PulseSensor::update_distribution);
}

void PulseSensor::update_distribution()
{
    m_dist = std::uniform_int_distribution<>(m_dist.min() - 10, m_dist.max() + 5);
    m_timer.start();
    if(m_dist.min() <= 30) {
        m_timer.stop();
    }
}


int PulseSensor::generate_pulse_reading()
{
    return m_dist(m_gen);
}

void PulseSensor::monitor_pulse()
{
    int pulse = generate_pulse_reading();
    qDebug() << "pulse: " << pulse;
    PulseEvent* event = new PulseEvent(QDateTime::currentDateTime(), QString::number(pulse), m_room);
    publish_event(event);
}


BloodPressureCuff::BloodPressureCuff(const QString &a_id, const QString &a_room, const QString &a_log, const QString &a_config)
    : Device(a_id, "BloodPressureCuff", a_room, a_log, a_config), m_gen(m_rd()), m_systolic_dist(110, 140), m_diastolic_dist(60, 90)
{
    QTimer::singleShot(30000, this, &BloodPressureCuff::update_distribution);
    m_timer.setInterval(10000);
    QObject::connect(&m_timer, &QTimer::timeout, this, &BloodPressureCuff::update_distribution);
}

void BloodPressureCuff::update_distribution()
{
    m_systolic_dist = std::uniform_int_distribution<>(m_systolic_dist.min() - 10, m_systolic_dist.max() - 5);
    m_diastolic_dist = std::uniform_int_distribution<>(m_diastolic_dist.min() - 5, m_diastolic_dist.max() - 3);
    m_timer.start();
    if(m_systolic_dist.min() <= 50 || m_diastolic_dist.min() <= 30) {
        m_timer.stop();
    }
}

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
    : Device(a_id, "Oximeter", a_room, a_log, a_config), m_gen(m_rd()), m_dist(98, 100)
{
    QTimer::singleShot(30000, this, &Oximeter::update_distribution);
    m_timer.setInterval(10000);
    QObject::connect(&m_timer, &QTimer::timeout, this, &Oximeter::update_distribution);
}

void Oximeter::update_distribution()
{
    m_dist = std::uniform_int_distribution<>(m_dist.min() - 1, m_dist.max() - 1);
    m_timer.start();
    if(m_dist.min() <= 45){
        m_timer.stop();
    }
}

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

    qDebug() << "saturation: " << saturation;
}


Thermometer::Thermometer(const QString &a_id, const QString &a_room, const QString &a_log, const QString &a_config)
    : Device(a_id, "Thermometer", a_room, a_log, a_config), m_gen(m_rd()), m_dist(36.0, 36.9)
{
    // QTimer::singleShot(60000, this, &Thermometer::update_distribution);
    // m_timer.setInterval(10000);
    // QObject::connect(&m_timer, &QTimer::timeout, this, &Thermometer::update_distribution);
}

// void Thermometer::update_distribution()
// {
//     m_dist = std::uniform_real_distribution<>(m_dist.min() - 0.2, m_dist.max() - 0.2); 
//     m_timer.start();
//     // if(m_dist.min() <= 35.0){
//     //     m_timer.stop();
//     // }
// }
double Thermometer::generate_temperature_reading()
{
    return m_dist(m_gen);
}

void Thermometer::monitor_temperature()
{
    double temperature = generate_temperature_reading();
    TemperatureEvent* event = new TemperatureEvent(QDateTime::currentDateTime(), QString::number(temperature), m_room);
    publish_event(event);

    qDebug() << "temperature: " << temperature;
}
