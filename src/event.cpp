#include "event.hpp"
#include <QDataStream>

Event::Event(const QDateTime& time, const QString& type, const QString& data, const QString& location)
    : timestamp(time),
      eventType(type),
      eventData(data),
      eventLocation(location)
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

void Event::set_abnormal(const QString& a_value)
{
    eventType = a_value;
}

bool is_abnormal(const QString& a_type)
{
    if (a_type == "ABNORMAL PULSE" || a_type == "ABNORMAL BP" || a_type == "ABNORMAL SAT" || a_type == "ABNORMAL TEMP")
    {
        return true;
    }

    return false;
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
