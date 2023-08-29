// pulse_event_handler.hpp
#ifndef PULSE_EVENT_HANDLER_HPP
#define PULSE_EVENT_HANDLER_HPP

#include "event.hpp"

class PulseEventHandler
{
public:
    PulseEventHandler() = default;
    void handleEvent(const Event& event);
};

#endif // PULSE_EVENT_HANDLER_HPP