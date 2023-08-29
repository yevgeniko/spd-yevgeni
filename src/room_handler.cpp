// room_handler.cpp
#include "room_handler.hpp"

RoomHandler::RoomHandler()
{
    pulseHandler = std::make_unique<PulseEventHandler>(60, 100);
    // Initialize other handlers here if necessary
}

RoomHandler::RoomHandler(RoomHandler&& other) noexcept
    : pulseHandler(std::move(other.pulseHandler))
{
    // move other members if necessary
}

RoomHandler& RoomHandler::operator=(RoomHandler&& other) noexcept
{
    if (this != &other)
    {
        pulseHandler = std::move(other.pulseHandler);
        // move other members if necessary
    }
    return *this;
}

bool RoomHandler::get_pulse_handler_flag()
{
    return m_is_pulse_handler_connected;
}

void RoomHandler::set_pulse_handler_flag(bool a_value)
{
    m_is_pulse_handler_connected = a_value;
}