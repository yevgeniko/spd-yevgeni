#include "server_device.hpp"

namespace dashboard {

ServerDevice::ServerDevice(const std::string& deviceID, const std::string& type,
    const std::string& room, const std::string& configuration)
: m_deviceID(deviceID)
, m_type(type)
, m_room(room)
, m_configuration(configuration) 
{
}


} // namespace dashboard
