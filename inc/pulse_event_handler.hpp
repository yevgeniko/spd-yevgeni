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

#endif // PULSE_EVENT_HANDLER_HPP
