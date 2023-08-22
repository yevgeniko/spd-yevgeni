#include "server.hpp"

#include <memory>

namespace dashboard{


Server::Server()
:m_device_config("file_INI")
{
    create_devices();
}

void Server::create_devices()
{
    for (const DeviceStruct& device_info : m_device_config.m_devices) {
        std::unique_ptr<ServerDevice> device = std::make_unique<ServerDevice>(device_info.device_ID,
            device_info.type, device_info.room, device_info.configuration);
        m_device_pointers.push_back(std::move(device));
    }
}


} // namespace dashboard