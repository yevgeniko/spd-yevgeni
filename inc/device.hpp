// device.hpp
#ifndef DEVICE_HPP
#define DEVICE_HPP

#include <QString>
#include <memory>
#include "device_manager.hpp"

class Device
{
public:
    Device(const QString &a_id, const QString &a_t, const QString &a_r, const QString &a_log, const QString &a_config);
    virtual ~Device();

    virtual void publish_event(Event* a_event);
    DeviceManager* get_manager() const;

protected:
    QString m_deviceID;
    QString m_type;
    QString m_room;
    QString m_logName;
    QString m_configuration;

    std::unique_ptr<DeviceManager> m_manager;
};

#endif // DEVICE_HPP
