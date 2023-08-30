#include "pulse_event_handler.hpp"
#include <QDebug>

PulseEventHandler::PulseEventHandler(qint16 lower_limit, qint16 higher_limit)
    : EventHandlerBase(lower_limit, higher_limit) {}

void PulseEventHandler::handleEvent(const Event& event)
{
    qDebug() << "IN Pulse Event Handler with data:" << event.getEventData();
    int room_number = event.getEventLocation().toInt();
    // int room_number = 1;

    if (event.getEventData().toInt() < m_lower_limit || event.getEventData().toInt() > m_higher_limit) {
        emit alertGenerated(event);  // Emit the alert signal
    }

    emit eventProcessed(room_number, event); // Emit the processed event signal
}