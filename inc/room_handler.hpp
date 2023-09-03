// room_handler.hpp
#ifndef ROOM_HANDLER_HPP
#define ROOM_HANDLER_HPP

#include "pulse_event_handler.hpp"
#include <memory>
#include "server_manager.hpp"
//more handlers here like BloodPressureEventHandler etc.

class PulseEventHandler;

class RoomHandler
{
public:
    RoomHandler();
    RoomHandler(const RoomHandler&) = delete;
    RoomHandler(RoomHandler&& other) noexcept;
    RoomHandler& operator=(const RoomHandler&) = delete;
    RoomHandler& operator=(RoomHandler&& other) noexcept;

    std::unique_ptr<PulseEventHandler> pulseHandler;
    bool get_pulse_handler_flag();
    void set_pulse_handler_flag(bool a_value);

    std::unique_ptr<SaturationEventHandler> saturationHandler;
    bool get_saturation_handler_flag();
    void set_saturation_handler_flag(bool a_value);
    
    std::unique_ptr<TemperatureEventHandler> temperatureHandler;
    bool get_temperature_handler_flag();
    void set_temperature_handler_flag(bool a_value);

    std::unique_ptr<BloodPressureEventHandler> bloodPressureHandler;
    bool get_bloodpressure_handler_flag();
    void set_bloodpressure_handler_flag(bool a_value);

private:
    bool m_is_pulse_handler_connected = false;
    bool m_is_saturation_handler_connected = false;
    bool m_is_temperature_handler_connected = false;
    bool m_is_bloodpressure_handler_connected = false;
    

};


#endif // ROOM_HANDLER_HPP