#ifndef DEVICE_MANAGER_HPP
#define DEVICE_MANAGER_HPP

#include <QObject>
#include <QList>
#include <QTcpSocket>
#include <QDataStream>
#include <QDateTime>
#include <QScopedPointer>
#include "event.hpp"

class Device;
class Event;

class DeviceManager : public QObject
{
    Q_OBJECT

public:
    DeviceManager();
    ~DeviceManager();

    void receive_event(Event* a_event);
    void connect_to_server(const QString &a_address, quint16 a_port);
    void send_event_to_server(Event* a_event);

private slots:
    // void on_connected();
    void on_data_received();
    // void on_error(QAbstractSocket::SocketError socketError);

private:
    QScopedPointer<QTcpSocket> m_socket;
    quint16 m_block_size;
};

#endif // DEVICE_MANAGER_HPP

