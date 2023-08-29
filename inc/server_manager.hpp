#ifndef SERVER_MANAGER_HPP
#define SERVER_MANAGER_HPP

#include <vector>
#include <memory>

#include "simple_server.hpp"
#include "device_config.hpp"
#include "agent.hpp"
#include "event_from_server.hpp"

using namespace dashboard;

class ServerManager : public QObject {
    Q_OBJECT
public:
    ServerManager();
    void start_services();
    void create_devices();
    const std::vector<std::unique_ptr<Agent>>& server_devices() const;
    void connect_to_agent();
    void send_event(const QString& room_number); 


private:
    SimpleServer m_simple_server_instance; //TCP SERVER FOR SENSORS
    // dashboard::AgentManager m_agent_manager;
    dashboard::DeviceConfig m_device_config;

private:
   std::vector<std::unique_ptr<Agent>> m_agents_pointers;

};

#endif // SERVER_MANAGER_HPP
