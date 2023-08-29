// room_handler.cpp
#include "room_handler.hpp"

RoomHandler::RoomHandler()
{
    pulseHandler = std::make_unique<PulseEventHandler>();
    // Initialize other handlers here if necessary
}