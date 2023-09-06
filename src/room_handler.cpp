// room_handler.cpp
#include "room_handler.hpp"

RoomHandler::RoomHandler()
{
    pulseHandler = std::make_unique<PulseEventHandler>(60, 100);
    saturationHandler = std::make_unique<SaturationEventHandler>(91, 100);
    temperatureHandler = std::make_unique<TemperatureEventHandler>(36, 38);
    bloodPressureHandler = std::make_unique<BloodPressureEventHandler>(90, 140, 60, 90);
}

RoomHandler::RoomHandler(RoomHandler&& other) noexcept
    : pulseHandler(std::move(other.pulseHandler))
    , saturationHandler(std::move(other.saturationHandler))
    , temperatureHandler(std::move(other.temperatureHandler))
    , bloodPressureHandler(std::move(other.bloodPressureHandler))
{
}


RoomHandler& RoomHandler::operator=(RoomHandler&& other) noexcept
{
    if (this != &other)
    {
        pulseHandler = std::move(other.pulseHandler);
        saturationHandler = std::move(other.saturationHandler);
        temperatureHandler = std::move(other.temperatureHandler);
        bloodPressureHandler = std::move(other.bloodPressureHandler);

        m_is_pulse_handler_connected = other.m_is_pulse_handler_connected;
        m_is_saturation_handler_connected = other.m_is_saturation_handler_connected;
        m_is_temperature_handler_connected = other.m_is_temperature_handler_connected;
        m_is_bloodpressure_handler_connected = other.m_is_bloodpressure_handler_connected;

        other.m_is_pulse_handler_connected = false;
        other.m_is_saturation_handler_connected = false;
        other.m_is_temperature_handler_connected = false;
        other.m_is_bloodpressure_handler_connected = false;
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

bool RoomHandler::get_saturation_handler_flag()
{
    return m_is_saturation_handler_connected;
}

void RoomHandler::set_saturation_handler_flag(bool a_value)
{
    m_is_saturation_handler_connected = a_value;
}

bool RoomHandler::get_temperature_handler_flag()
{
    return m_is_temperature_handler_connected;
}

void RoomHandler::set_temperature_handler_flag(bool a_value)
{
    m_is_temperature_handler_connected = a_value;
}

bool RoomHandler::get_bloodpressure_handler_flag()
{
    return m_is_bloodpressure_handler_connected;
}

void RoomHandler::set_bloodpressure_handler_flag(bool a_value)
{
    m_is_bloodpressure_handler_connected = a_value;
}
