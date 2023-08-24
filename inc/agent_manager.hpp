#ifndef SERVER_HPP
#define SERVER_HPP

#include <vector>
#include <memory>

#include "device_config.hpp"
#include "agent.hpp"


namespace dashboard{

class DeviceManager;
class ClientServerManager;
// class Logger;
class DeviceConfig;

class AgentManager{

public:
    AgentManager();
    void create_devices();
    const std::vector<std::unique_ptr<Agent>>& server_devices() const;

private:
    // DeviceManager m_dm;
    // ClientServerManager m_csm;
    // Logger m_logger;
    DeviceConfig m_device_config;

private:
   std::vector<std::unique_ptr<Agent>> m_device_pointers;
};


} // namespace dashboard



#endif // SERVER_HPP