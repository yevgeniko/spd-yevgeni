#include "event.hpp"

Event::Event(const QString& type, const QString& data, const QString& location)
    : timestamp(QDateTime::currentDateTime()), eventType(type), eventData(data), eventLocation(location) {}

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

PulseEvent::PulseEvent(const QString& pulseData, const QString& location)
    : Event("Pulse", pulseData, location)
    {}
