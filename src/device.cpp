// device.cpp
#include "device.hpp"

Device::Device(const QString &a_id, const QString &a_t, const QString &a_r, const QString &a_log, const QString &a_config)
    : m_deviceID(a_id), m_type(a_t), m_room(a_r), m_logName(a_log), m_configuration(a_config) 
{
    m_manager = std::make_unique<DeviceManager>();
}

Device::~Device() = default;  // the unique_ptr will automatically delete the manager

void Device::publish_event(Event* a_event)
{
    if (m_manager) m_manager->receive_event(a_event);
}

DeviceManager* Device::get_manager() const 
{
    return m_manager.get();
}
