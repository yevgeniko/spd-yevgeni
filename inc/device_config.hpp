#ifndef DEVICE_CONFIG_HPP
#define DEVICE_CONFIG_HPP

#include <string>
#include <vector>

#include "server.hpp"

namespace dashboard {

struct DeviceStruct {
    std::string device_ID;
    std::string type;
    std::string room;
    std::string configuration;
};

class DeviceConfig {
public:

    DeviceConfig(const std::string& a_config_file);

    friend class Server;

private:
    void read_from_file(const std::string& a_config_file);   
private:

    std::vector<DeviceStruct> m_devices;
};

} // namespace dashboard

#endif // DEVICE_CONFIG_HPP
