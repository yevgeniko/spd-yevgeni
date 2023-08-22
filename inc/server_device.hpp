#ifndef SERVER_DEVICE_HPP
#define SERVER_DEVICE_HPP

#include <string>

namespace dashboard {

class ServerDevice {
public:
    public:
    ServerDevice(const std::string& a_device_ID, const std::string& a_type,
        const std::string& a_room, const std::string& a_configuration);


private:
    std::string m_deviceID;
    std::string m_type;
    std::string m_room;
    std::string m_configuration;
};

} // namespace dashboard

#endif // SERVER_DEVICE_HPP