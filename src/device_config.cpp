#include "device_config.hpp"

#include <fstream>
#include <stdexcept>
#include <iostream>


// #include <QSettings>
// #include <QDebug>


namespace dashboard{

DeviceConfig::DeviceConfig(const QString& a_config_file)
{
    read_from_file(a_config_file);
}


void DeviceConfig::read_from_file(const QString& a_config_file) {
    QSettings settings(a_config_file, QSettings::IniFormat);

    QStringList sections = settings.childGroups();

    for (const QString& section : sections) {
        settings.beginGroup(section);

        QString deviceID = settings.value("deviceID").toString();
        QString type = settings.value("type").toString();
        QString room = settings.value("room").toString();
        QString configuration = settings.value("configuration").toString();

        DeviceStruct current_device;
        current_device.device_ID = deviceID;
        current_device.type = type;
        current_device.room = room;
        current_device.configuration = configuration;

        m_devices.push_back(current_device);

        settings.endGroup(); 
    }
}



} //namespace dashboard