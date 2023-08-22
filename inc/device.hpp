#ifndef DEVICE_HPP
#define DEVICE_HPP

#include <QString>
#include "device_manager.hpp"

class Device
{

public:
    Device(const QString &id, const QString &t, const QString &r, const QString &log, const QString &config);
    virtual ~Device();

    void setManager(DeviceManager* mgr) { manager = mgr; }
    virtual void publishEvent(Event* event) { if (manager) manager->receiveEvent(event); }


protected:
    QString deviceID;
    QString type;
    QString room;
    QString logName;
    QString configuration;

    DeviceManager* manager = nullptr;


    // Getters and Setter
};

#endif // DEVICE_HPP
