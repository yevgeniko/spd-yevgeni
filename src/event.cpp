#include "event.hpp"
#include <QDataStream>

Event::Event(const QDateTime& time, const QString& type, const QString& data, const QString& location)
    : timestamp(time),
      eventType(type),
      eventData(data),
      eventLocation(location),
      m_is_abnormal(false)
    {}

Event& Event::operator=(const Event& other) 
{
    if (this != &other)
    {
        timestamp = other.timestamp;
        eventType = other.eventType;
        eventData = other.eventData;
        eventLocation = other.eventLocation;
    }
    return *this;
}


QDateTime Event::getTimestamp() const
{
    return timestamp;
}

QString Event::getEventType() const
{
    return eventType;
}

QString Event::getEventData() const
{
    return eventData;
}

QString Event::getEventLocation() const
{
    return eventLocation;
}


bool Event::is_abnormal() const
{
    return m_is_abnormal;
}

void Event::set_abnormal(bool a_value)
{
    m_is_abnormal = a_value;
}

void Event::setEventType(const QString& type)
{
    eventType = type;
}


PulseEvent::PulseEvent(const QDateTime& time, const QString& pulseData, const QString& location)
    : Event(time, "PULSE", pulseData, location)
{}


PressureEvent::PressureEvent(const QDateTime& time, const QString& pressureData, const QString& location)
    : Event(time, "BP", pressureData, location)
{}


SaturationEvent::SaturationEvent(const QDateTime& time, const QString& saturationData, const QString& location)
    : Event(time, "SAT", saturationData, location)
{}

TemperatureEvent::TemperatureEvent(const QDateTime& time, const QString& temperatureData, const QString& location)
    : Event(time, "TEMP", temperatureData, location)
{}
