#include "device_manager.hpp"
#include "event.hpp"
#include <stdio.h>

DeviceManager::DeviceManager()
{
    socket = new QTcpSocket(this);
    blockSize = 0;

    // Connect signals and slots
    //connect(socket, &QTcpSocket::connected, this, &DeviceManager::onConnected);
    connect(socket, &QTcpSocket::readyRead, this, &DeviceManager::onDataReceived); // To handle incoming data
    //connect(socket, static_cast<void (QTcpSocket::*)(QAbstractSocket::SocketError)>(&QTcpSocket::error), this, &DeviceManager::onError);
}

DeviceManager::~DeviceManager()
{
    socket->close();
    delete socket;
}

void DeviceManager::connectToServer(const QString &address, quint16 port)
{
    socket->connectToHost(address, port);
}

void DeviceManager::sendEventToServer(Event* event)
{
    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);

    out << (quint16)0;
    out << event->getTimestamp() << event->getEventType() << event->getEventData() << event->getEventLocation();


    out.device()->seek(0);
    out << (quint16)(block.size() - sizeof(quint16));

    socket->write(block);
}

void DeviceManager::onDataReceived()
{
    QDataStream in(socket);

    if (blockSize == 0)
    {
        if (socket->bytesAvailable() < (int)sizeof(quint16))
            return; 
        in >> blockSize;
    }

    if (socket->bytesAvailable() < blockSize)
    {
       return;
    }

    QDateTime timeStamp;
    QString eventType;
    QString eventData;
    QString eventLocation;
    in >> timeStamp >> eventType >> eventData >> eventLocation;


    blockSize = 0; // Reset block size for next message
}

// void DeviceManager::onConnected()
// {
//     // Handle what you want to do once connected, like sending initial setup data
// }

// void DeviceManager::onError(QAbstractSocket::SocketError socketError)
// {
//     // void* temp = (QAbstractSocket::SocketError) socketError;
// }

// void DeviceManager::registerDevice(Device* device)
// {
//     devices.append(device);
// }

void DeviceManager::receiveEvent(Event* event)
{
    sendEventToServer(event);
}

