#include "server_device.hpp"

namespace dashboard {

ServerDevice::ServerDevice(const QString& deviceID, const QString& type,
    const QString& room, const QString& configuration)
: m_deviceID(deviceID)
, m_type(type)
, m_room(room)
, m_configuration(configuration) 
{
}

const QString& ServerDevice::getDeviceID() const {
    return m_deviceID;
}

const QString& ServerDevice::getType() const {
    return m_type;
}

const QString& ServerDevice::getRoom() const {
    return m_room;
}

const QString& ServerDevice::getConfiguration() const {
    return m_configuration;
}

} // namespace dashboard
