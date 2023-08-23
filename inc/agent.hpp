#ifndef AGENT_HPP
#define AGENT_HPP

#include <string>
#include <QSettings>

#include "logger.hpp"

// class Logger;


namespace dashboard {

 class Logger;

class Agent {
public:
    public:
    Agent(const QString& a_device_ID, const QString& a_type,
        const QString& a_room, const QString& a_configuration);

    const QString& getDeviceID() const;
    const QString& getType() const;
    const QString& getRoom() const;
    const QString& getConfiguration() const;

    void log_unNormal(const QString& a_even_type, const QString& a_event_message);


private:
    QString m_deviceID;
    QString m_type;
    QString m_room;
    QString m_configuration;
    Logger m_logger;

};

} // namespace dashboard

#endif // AGENT_HPP