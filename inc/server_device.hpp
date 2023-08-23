#ifndef SERVER_DEVICE_HPP
#define SERVER_DEVICE_HPP

#include <string>
#include <QSettings>


namespace dashboard {

class ServerDevice {
public:
    public:
    ServerDevice(const QString& a_device_ID, const QString& a_type,
        const QString& a_room, const QString& a_configuration);

    const QString& getDeviceID() const;
    const QString& getType() const;
    const QString& getRoom() const;
    const QString& getConfiguration() const;

private:
    QString m_deviceID;
    QString m_type;
    QString m_room;
    QString m_configuration;
};

} // namespace dashboard

#endif // SERVER_DEVICE_HPP