#ifndef DEVICE_CONFIG_HPP
#define DEVICE_CONFIG_HPP

#include <string>
#include <vector>

#include <QSettings>
#include <QDebug>
#include <QCoreApplication>

#include "server_manager.hpp"


namespace dashboard {

struct DeviceStruct {
    QString device_ID;
    QString type;
    QString room;
    QString configuration;
};

class DeviceConfig {
public:

    DeviceConfig(const QString& a_config_file);


private:
    void read_from_file(const QString& a_config_file);   
private:

    std::vector<DeviceStruct> m_devices;

    friend class ServerManager;
};

} // namespace dashboard

#endif // DEVICE_CONFIG_HPP
