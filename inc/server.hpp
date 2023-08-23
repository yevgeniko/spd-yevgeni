#ifndef SERVER_HPP
#define SERVER_HPP

#include <unordered_map>
#include <vector>
#include <memory>

#include "device_config.hpp"
#include "server_device.hpp"


namespace dashboard{

class DeviceManager;
class ClientServerManager;
class Logger;
class DeviceConfig;

class Server{

public:
    Server();
    void create_devices();
    const std::vector<std::unique_ptr<ServerDevice>>& server_devices() const;

private:
    // DeviceManager m_dm;
    // ClientServerManager m_csm;
    // Logger m_logger;
    DeviceConfig m_device_config;

private:
   std::vector<std::unique_ptr<ServerDevice>> m_device_pointers;
};


} // namespace dashboard



#endif // SERVER_HPP