#include "event.hpp"

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
        m_event_ID = other.m_event_ID;
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

QString Event::get_event_ID() const
{
    return m_event_ID;
}

PulseEvent::PulseEvent(const QDateTime& time, const QString& pulseData, const QString& location)
    : Event(time, "Pulse", pulseData, location)
{}


void Event::set_ID(const QString& ID)
{
    m_event_ID = ID;
}