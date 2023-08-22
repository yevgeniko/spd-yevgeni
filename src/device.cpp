#include "device.hpp"

Device::Device(const QString &id, const QString &t, const QString &r, const QString &log, const QString &config)
    : deviceID(id), type(t), room(r), logName(log), configuration(config) {}

Device::~Device()
{
}
