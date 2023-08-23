#ifndef DEVICE_MANAGER_HPP
#define DEVICE_MANAGER_HPP

#include <QObject>
#include <QList>
#include <QTcpSocket>
#include <QDataStream>
#include <QDateTime>
#include "event.hpp"

class Device;
class Event;

class DeviceManager : public QObject
{
    Q_OBJECT

public:
    DeviceManager();
    ~DeviceManager();

    void receiveEvent(Event* event);
    void connectToServer(const QString &address, quint16 port);
    void sendEventToServer(Event* event);

private slots:
    // void onConnected();
    void onDataReceived();
    // void onError(QAbstractSocket::SocketError socketError);


private:
    QTcpSocket *socket;
    quint16 blockSize;
};

#endif // DEVICE_MANAGER_HPP
