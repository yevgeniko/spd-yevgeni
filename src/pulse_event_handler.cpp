// pulse_event_handler.cpp
#include "pulse_event_handler.hpp"
#include "room_handler.hpp"

#include <QDebug>

void PulseEventHandler::handleEvent(const Event& event)
{
    // just logging the event for now
    qDebug() << "Handled Pulse Event with data:" << event.getEventData();
}
