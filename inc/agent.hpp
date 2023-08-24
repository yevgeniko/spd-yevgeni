#ifndef AGENT_HPP
#define AGENT_HPP

#include <string>
#include <QSettings>

#include "logger.hpp"
#include "event.hpp"

// class Logger;


namespace dashboard {

class Logger;

enum class ProcessResult {
    ConfigurationSent, 
    RegularMessage      
};

class Agent {
public:
    public:
    Agent(const QString& a_device_ID, const QString& a_type,
        const QString& a_room, const QString& a_configuration);

    const QString& getAgentID() const;
    const QString& getType() const;
    const QString& getRoom() const;
    const QString& getConfiguration() const;

    ProcessResult procces_event(const Event& a_event);
    void log_unNormal(const QString& a_even_type, const QString& a_event_message);


private:
    QString m_agent_ID;
    QString m_type;
    QString m_room;
    QString m_configuration;
    Logger m_logger;
    bool m_configuration_sent;

};

} // namespace dashboard

#endif // AGENT_HPP