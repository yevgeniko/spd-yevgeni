#include "agent_manager.hpp"

#include <memory>

namespace dashboard{


AgentManager::AgentManager()
:m_device_config("devices.ini")
{
    create_devices();
}

void AgentManager::create_devices()
{
    for (const DeviceStruct& device_info : m_device_config.m_devices) {
        std::unique_ptr<Agent> device = std::make_unique<Agent>(device_info.device_ID,
            device_info.type, device_info.room, device_info.configuration);
        m_device_pointers.push_back(std::move(device));
    }
}

const std::vector<std::unique_ptr<Agent>>& AgentManager::server_devices() const {
    return m_device_pointers;
}

} // namespace dashboard