#ifndef SERVER_HPP
#define SERVER_HPP

#include <unordered_map>
#include <vector>


namespace dashboard{

class DeviceManager;
class ClientServerManager;
class Logger;
class DeviceConfig;

class Server{

public:
    Server();

private:
    // DeviceManager m_dm;
    // ClientServerManager m_csm;
    // Logger m_logger;
    // DeviceConfig m_device_config;

private:
    // std::unordered_map<int, std::vector<monitor>> m_rooms;
};


} // namespace dashboard



#endif // SERVER_HPP