#include "client_TCP.hpp"

namespace spd {

ClientTCP::ClientTCP() : m_server{std::make_unique<QTcpServer>(this)}, m_socket{nullptr} {
    connect(m_server.get(), &QTcpServer::newConnection, this, &ClientTCP::onNewConnection);
}

ClientTCP::~ClientTCP() {
    if (m_socket) {
        m_socket->close();
    }
}

void ClientTCP::onNewConnection() {
    m_socket = m_server->nextPendingConnection();

    if (!m_socket) return;

    connect(m_socket, &QTcpSocket::readyRead, this, &ClientTCP::onDataReceived);
    connect(m_socket, &QTcpSocket::connected, [=](){
        qDebug() << "Connected to server!";
    });
    connect(m_socket, &QTcpSocket::disconnected, [=](){
        qDebug() << "Disconnected from server!";
    });
    connect(m_socket, static_cast<void (QTcpSocket::*)(QTcpSocket::SocketError)>(&QTcpSocket::error), [=](QTcpSocket::SocketError error){
        Q_UNUSED(error);
        qDebug() << "Connection Error:" << m_socket->errorString();
    });
}


void ClientTCP::startListening(const QString &address, quint16 port)
{
    if (!m_server->listen(QHostAddress(address), port)) {
        qCritical() << "Client could not start listening!";
    } else {
        qDebug() << "Client started listening!";
    }
}

void ClientTCP::onDataReceived()
{
    QDataStream in(m_socket);
    quint16 blockSize = 0;

    if (blockSize == 0) {
        if (m_socket->bytesAvailable() < (int)sizeof(quint16)) {
            return; 
        }
        in >> blockSize;
    }

    if (m_socket->bytesAvailable() < blockSize) {
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
}


void ClientTCP::send_request(const Request& a_request)
{
    if (!m_socket) {
        qDebug() << "Socket not connected.";
        return;
    }

    QByteArray data;
    QDataStream out(&data, QIODevice::WriteOnly);

    out << a_request.request_type << a_request.room_number;

    quint16 blockSize = data.size();
    m_socket->write(reinterpret_cast<const char*>(&blockSize), sizeof(quint16));
    m_socket->write(data);
    qDebug() << " request is sent \n";    

}


} // namespace spd