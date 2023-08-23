#include "client_manager.hpp"
#include "event.hpp"

namespace spd {

spd::ClientManager::ClientManager()
: m_socket{std::make_unique<QTcpSocket>(this)}
, m_block_size{0}
{
    connect(m_socket.get(), &QTcpSocket::readyRead, this, &ClientManager::onDataReceived);
}

ClientManager::~ClientManager()
{
    m_socket->close();
}

void ClientManager::onDataReceived() 
{
    QDataStream in(m_socket.get());

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

    m_block_size = 0; // Reset block size for next message
}

void ClientManager::connect_to_server(const QString &address, quint16 port)
{
    m_socket.get()->connectToHost(address, port);
}
void ClientManager::onNewConnection()
{
}
} // namespace spd
