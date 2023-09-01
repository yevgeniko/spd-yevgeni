#ifndef EVENT_HPP
#define EVENT_HPP

#include <QString>
#include <QDateTime>

class Event
{
public:
    Event(const QDateTime& time, const QString& type, const QString& data, const QString& location);
    virtual ~Event() = default;
    Event& operator=(const Event& other);


    // Getters
    QDateTime getTimestamp() const;
    QString getEventType() const;
    QString getEventData() const;
    QString getEventLocation() const;

    // QString get_event_ID() const;
    // void set_ID(const QString& ID);

protected:
    QDateTime timestamp;
    QString eventType;
    QString eventData;
    QString eventLocation;
    // QString m_event_ID;

};

class PulseEvent : public Event
{
public:
    PulseEvent(const QDateTime& time, const QString& pulseData, const QString& location);
};


#endif // EVENT_HPP
