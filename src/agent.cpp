#include "agent.hpp"

namespace dashboard {

Agent::Agent(const QString& deviceID, const QString& type,
    const QString& room, const QString& configuration)
: m_deviceID(deviceID)
, m_type(type)
, m_room(room)
, m_configuration(configuration) 
, m_logger(deviceID)
{
}

const QString& Agent::getDeviceID() const {
    return m_deviceID;
}

const QString& Agent::getType() const {
    return m_type;
}

const QString& Agent::getRoom() const {
    return m_room;
}

const QString& Agent::getConfiguration() const {
    return m_configuration;
}

void Agent::log_unNormal(const QString& a_even_type, const QString& a_event_message)
{
    m_logger.log_event(a_even_type, a_event_message);
}

} // namespace dashboard
