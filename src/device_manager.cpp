#include "device_manager.hpp"
#include "event.hpp"
#include <stdio.h>

DeviceManager::DeviceManager()
    : m_socket(new QTcpSocket(this))
    , m_block_size(0)
{
    connect(m_socket.data(), &QTcpSocket::readyRead, this, &DeviceManager::on_data_received);
}

DeviceManager::~DeviceManager()
{
    m_socket->close();
}

void DeviceManager::connect_to_server(const QString &a_address, quint16 a_port)
{
    m_socket->connectToHost(a_address, a_port);
}

void DeviceManager::send_event_to_server(Event* a_event)
{
    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);

    out << (quint16)0;
    out << a_event->getTimestamp() << a_event->getEventType() << a_event->getEventData() << a_event->getEventLocation();

    out.device()->seek(0);
    out << (quint16)(block.size() - sizeof(quint16));

    m_socket->write(block);
}

void DeviceManager::on_data_received()
{
    QDataStream in(m_socket.data());

    if (m_block_size == 0)
    {
        if (m_socket->bytesAvailable() < (int)sizeof(quint16))
            return;
        in >> m_block_size;
    }

    if (m_socket->bytesAvailable() < m_block_size)
    {
       return;
    }

    QDateTime timeStamp;
    QString eventType;
    QString eventData;
    QString eventLocation;
    in >> timeStamp >> eventType >> eventData >> eventLocation;

    m_block_size = 0;
}

void DeviceManager::receive_event(Event* a_event)
{
    send_event_to_server(a_event);
}
