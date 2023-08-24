#include "agent.hpp"

namespace dashboard {

Agent::Agent(const QString& deviceID, const QString& type,
    const QString& room, const QString& configuration)
: m_agent_ID(deviceID)
, m_type(type)
, m_room(room)
, m_configuration(configuration) 
, m_logger(deviceID)
{
}


const QString& Agent::getAgentID() const {
    return m_agent_ID;
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

ProcessResult Agent::procces_event(const Event& a_event)
{
    if(!m_configuration_sent){
        m_configuration_sent = true;
        return ProcessResult::ConfigurationSent;
    }
    int heart_rate = a_event.getEventData().toInt();
    if(heart_rate < 70 ){
        log_unNormal("unNormal Heart rate", "Heart rate low: " + a_event.getEventData());
        return ProcessResult::RegularMessage;
    }
    if(heart_rate > 120 ){ 
        log_unNormal("unNormal Heart rate", "Heart rate high: " + a_event.getEventData());
        return ProcessResult::RegularMessage;
    }
    return ProcessResult::RegularMessage;
}





} // namespace dashboard
