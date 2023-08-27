#ifndef EVENT_HPP
#define EVENT_HPP

#include <QString>
#include <QDateTime>

class Event
{
public:
    Event(const QString& type, const QString& data, const QString& location);
    virtual ~Event() = default;
    Event& operator=(const Event& other);


    // Getters
    QDateTime getTimestamp() const;
    QString getEventType() const;
    QString getEventData() const;
    QString getEventLocation() const;
    QString getSenderID() const;

protected:
    QDateTime timestamp;
    QString eventType;
    QString eventData;
    QString eventLocation;
    QString m_event_ID;

};

class PulseEvent : public Event
{
public:
    PulseEvent(const QString& pulseData, const QString& location);
};

#endif // EVENT_HPP
