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
    bool is_abnormal() const;
    void set_abnormal(bool a_value);
    
protected:
    QDateTime timestamp;
    QString eventType;
    QString eventData;
    QString eventLocation;
    bool m_is_abnormal;

};

class PulseEvent : public Event
{
public:
    PulseEvent(const QDateTime& time, const QString& pulseData, const QString& location);
};

class PressureEvent : public Event
{
public:
    PressureEvent(const QDateTime& time, const QString& pressureData, const QString& location);
};

class SaturationEvent : public Event
{
public:
    SaturationEvent(const QDateTime& time, const QString& saturationData, const QString& location);
};

class TemperatureEvent : public Event
{
public:
    TemperatureEvent(const QDateTime& time, const QString& temperatureData, const QString& location);
};


#endif // EVENT_HPP
