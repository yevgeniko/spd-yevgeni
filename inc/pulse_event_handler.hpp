#ifndef PULSE_EVENT_HANDLER_HPP
#define PULSE_EVENT_HANDLER_HPP

#include <QObject>
#include "event_handler_base.hpp"

class PulseEventHandler : public EventHandlerBase
{
    Q_OBJECT
public:
    PulseEventHandler(qint16 lower_limit = 60, qint16 higher_limit = 100);
    void handleEvent(Event& event) override;

signals:
    void alertGenerated(const Event& event);
    void eventProcessed(int room_number, const Event& event);
};


class BloodPressureEventHandler : public EventHandlerBase
{
    Q_OBJECT
public:
    BloodPressureEventHandler(qint16 lower_limit_systolic = 90, qint16 higher_limit_systolic = 140,
                              qint16 lower_limit_diastolic = 60, qint16 higher_limit_diastolic = 90);
    void handleEvent(const Event& event) override;

signals:
    void alertGenerated(const Event& event);
    void eventProcessed(int room_number, const Event& event);
private:
    qint16 m_lower_limit_diastolic;
    qint16 m_higher_limit_diastolic;
};

class SaturationEventHandler : public EventHandlerBase
{
    Q_OBJECT
public:
    SaturationEventHandler(qint16 lower_limit = 90, qint16 higher_limit = 100);
    void handleEvent(const Event& event) override;

signals:
    void alertGenerated(const Event& event);
    void eventProcessed(int room_number, const Event& event);
};

class TemperatureEventHandler : public EventHandlerBase
{
    Q_OBJECT
public:
    TemperatureEventHandler(qint16 lower_limit = 36, qint16 higher_limit = 38); // Assuming Celsius scale
    void handleEvent(const Event& event) override;

signals:
    void alertGenerated(const Event& event);
    void eventProcessed(int room_number, const Event& event);
};


#endif // PULSE_EVENT_HANDLER_HPP
