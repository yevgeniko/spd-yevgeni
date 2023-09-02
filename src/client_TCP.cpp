#include "client_TCP.hpp"
#include "event.hpp"

ClientTCP::ClientTCP() :
m_is_connected(false)
{
    m_socket.reset(new QTcpSocket(this));

    connect(m_socket.data(), &QTcpSocket::readyRead, this, &ClientTCP::on_data_received);
    connect(m_socket.data(), &QTcpSocket::connected, this, &ClientTCP::on_connected);
    connect(m_socket.data(), &QTcpSocket::disconnected, this, &ClientTCP::on_disconnected);
}

void ClientTCP::connectToServer(const QHostAddress &a_address, quint16 a_port)
{
    qDebug() << "Attempting to connect to server at" << a_address.toString() << "on port" << a_port;
    m_socket->connectToHost(a_address, a_port);
}

void ClientTCP::on_data_received()
{
    QDataStream in(m_socket.data());

    if(m_socket->bytesAvailable() < static_cast<qint64>(sizeof(quint16))) {
        return;
    }

    quint16 block_size;
    in >> block_size;

    if(m_socket->bytesAvailable() < static_cast<qint64>(block_size)) {
        return;
    }
    
    QDateTime time_stamp;
    QString event_type;
    QString event_data;
    QString event_location;
    in >> time_stamp >> event_type >> event_data >> event_location;

    qDebug() << "Received Event in CLIENT:";
    qDebug() << "Timestamp:" << time_stamp;
    qDebug() << "Event Type:" << event_type;
    qDebug() << "Event Data:" << event_data;
    qDebug() << "Event Location:" << event_location;

    emit newDataReceived(time_stamp, event_type, event_data, event_location);
}


void ClientTCP::on_connected()
{
    qDebug() << "Connected to server!";
    m_is_connected = true;
}

void ClientTCP::on_disconnected()
{
    qDebug() << "Disconnected from server!";
    m_is_connected = false;
}

void ClientTCP::sendRoomRequest(const Event &requestEvent)
{
    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);
    
    out << (quint16)0;
    out << requestEvent.getTimestamp() << requestEvent.getEventType() << requestEvent.getEventData() << requestEvent.getEventLocation();

    out.device()->seek(0);
    out << (quint16)(block.size() - sizeof(quint16));

    m_socket->write(block);
}

// void ClientTCP::requestInitialRoomEvents()
// {
//     qDebug() << "Connection established. Requesting initial room events.";
//     emit initialRoomRequestReady();
// }

bool ClientTCP::get_is_connected()
{
    return m_is_connected;
}