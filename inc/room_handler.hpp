// room_handler.hpp
#ifndef ROOM_HANDLER_HPP
#define ROOM_HANDLER_HPP

#include "pulse_event_handler.hpp"
#include <memory>
//more handlers here like BloodPressureEventHandler etc.

class RoomHandler
{
public:
    RoomHandler();

    std::unique_ptr<PulseEventHandler> pulseHandler;
    // other handler pointers as needed
};

#endif // ROOM_HANDLER_HPP