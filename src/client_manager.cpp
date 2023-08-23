#include "client_manager.hpp"
#include "event.hpp"

namespace spd {

ClientManager::ClientManager()
: m_socket{std::make_unique<QTcpSocket>(this)}
, m_block_size{0}
{
    serverListener = new QTcpServer(this);
    connect(serverListener, &QTcpServer::newConnection, this, &ClientManager::onNewConnection);
    serverListener->listen(QHostAddress::LocalHost, 5555);

    connect(m_socket.get(), &QTcpSocket::readyRead, this, &ClientManager::onDataReceived);

    connect(m_socket.get(), &QTcpSocket::connected, [=](){
        qDebug() << "Connected to server!";
    });

    connect(m_socket.get(), &QTcpSocket::disconnected, [=](){
        qDebug() << "Disconnected from server!";
    });

    connect(m_socket.get(), static_cast<void (QTcpSocket::*)(QTcpSocket::SocketError)>(&QTcpSocket::error), [=](QTcpSocket::SocketError error){
        Q_UNUSED(error);
        qDebug() << "Connection Error:" << m_socket->errorString();
    });
}


ClientManager::~ClientManager()
{
    m_socket->close();
}


void ClientManager::onDataReceived() 
{
    QTcpSocket* sourceSocket = qobject_cast<QTcpSocket*>(sender());

    if (!sourceSocket) {
        qDebug() << "Invalid source socket.";
        return;
    }

    if (sourceSocket == m_socket.get()) {
        qDebug() << "Data received from m_socket.";

        if (m_socket->state() != QTcpSocket::ConnectedState) {
            qDebug() << "Client socket not in connected state!";
            return;
        }
    } else if (sourceSocket == incomingSocket) {
        qDebug() << "Data received from incomingSocket.";
    } else {
        qDebug() << "Data received from an unknown socket.";
        return;
    }

    QDataStream in(sourceSocket);

    if (m_block_size == 0) {
        if (sourceSocket->bytesAvailable() < (int)sizeof(quint16)) {
            return; 
        }
        in >> m_block_size;
    }

    if (sourceSocket->bytesAvailable() < m_block_size) {
        qDebug() << "Not enough data available yet. Waiting for more...";
        return;
    }

    QDateTime timeStamp;
    QString eventType;
    QString eventData;
    QString eventLocation;
    in >> timeStamp >> eventType >> eventData >> eventLocation;

    qDebug() << "Received Event in CLIENT:";
    qDebug() << "Timestamp:" << timeStamp;
    qDebug() << "Event Type:" << eventType;
    qDebug() << "Event Data:" << eventData;
    qDebug() << "Event Location:" << eventLocation;

    emit newDataReceived(timeStamp, eventType, eventData, eventLocation);

    m_block_size = 0; // Reset block size for next message
}


void ClientManager::connect_to_server(const QString &address, quint16 port)
{
    m_socket->connectToHost(address, port);
}

void ClientManager::onNewConnection() {
    qDebug() << "Incoming connection detected in ClientManager!";
    incomingSocket = serverListener->nextPendingConnection();
    connect(incomingSocket, &QTcpSocket::readyRead, this, &ClientManager::onDataReceived);
}


} // namespace spd
