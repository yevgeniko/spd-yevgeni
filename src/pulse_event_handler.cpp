#include "pulse_event_handler.hpp"
#include <QDebug>

PulseEventHandler::PulseEventHandler(qint16 lower_limit, qint16 higher_limit)
    : EventHandlerBase(lower_limit, higher_limit) {}

void PulseEventHandler::handleEvent(Event& event)
{
    qDebug() << "IN Pulse Event Handler with data:" << event.getEventData();
    int room_number = event.getEventLocation().toInt();
    // m_logger.log_event(event.getEventType(), event.getEventData(), event.getEventLocation());

    if (event.getEventData().toInt() < m_lower_limit || event.getEventData().toInt() > m_higher_limit) {
        event.setEventType("ABNORMAL_PULSE");
        emit alertGenerated(event);
    }

    emit eventProcessed(room_number, event);
}