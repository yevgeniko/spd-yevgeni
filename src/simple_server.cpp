#include "simple_server.hpp"
#include "sensors.hpp"
#include "pulse_event_handler.hpp"

SimpleServer::SimpleServer()
{
    m_server.reset(new QTcpServer(this));
    m_forwarding_socket.reset(new QTcpSocket(this));
    m_client_server.reset(new QTcpServer(this)); 

    connect(m_server.data(), &QTcpServer::newConnection, this, &SimpleServer::on_new_connection);
    
    if (!m_server->listen(QHostAddress::LocalHost, 12345)) {
        qCritical() << "Server could not start!";
    } else {
        qDebug() << "Server started!";
    }

    // Start the client listener
    start_client_listener(QHostAddress::LocalHost, 5555);
}


void SimpleServer::on_new_connection()
{
    QTcpSocket *client_socket = m_server->nextPendingConnection();
    connect(client_socket, &QTcpSocket::readyRead, this, &SimpleServer::on_sensor_data_received);
    connect(client_socket, &QTcpSocket::disconnected, client_socket, &QTcpSocket::deleteLater);
}


void SimpleServer::start_client_listener(const QHostAddress &a_address, quint16 a_port) {
    connect(m_client_server.data(), &QTcpServer::newConnection, this, &SimpleServer::on_client_connected);
    if (!m_client_server->listen(a_address, a_port)) {
        qCritical() << "Could not start client listener!";
    } else {
        qDebug() << "Started client listener!";
    }
}

void SimpleServer::on_client_connected() {
    m_forwarding_socket.reset(m_client_server->nextPendingConnection());
    connect(m_forwarding_socket.data(), &QTcpSocket::readyRead, this, &SimpleServer::on_client_data_received);
    qDebug() << "Client connected for forwarding!";
}

void SimpleServer::forward_data(const QDateTime &time_stamp, const QString &event_type, const QString &event_data, const QString &event_location) {
    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);

    out << (quint16)0;
    out << time_stamp << event_type << event_data << event_location;

    out.device()->seek(0);
    out << (quint16)(block.size() - sizeof(quint16));

    if(m_forwarding_socket->state() == QTcpSocket::ConnectedState) {
        m_forwarding_socket->write(block);
    } else {
        qDebug() << "Failed to forward data because m_forwarding_socket is not connected.";
    }
}

void SimpleServer::on_sensor_data_received()
{
    QTcpSocket *client_socket = qobject_cast<QTcpSocket *>(sender());
    if (!client_socket)
        return;

    QDataStream in(client_socket);

    quint16 block_size;
    in >> block_size;

    if (client_socket->bytesAvailable() < block_size) {
        return;  // We don't have the complete data yet.
    }

    QDateTime time_stamp;
    QString event_type;
    QString event_data;
    QString event_location;
    in >> time_stamp >> event_type >> event_data >> event_location;

    qDebug() << "Received Event in SERVER from sensor:";
    qDebug() << "Timestamp:" << time_stamp;
    qDebug() << "Event Type:" << event_type;
    qDebug() << "Event Data:" << event_data;
    qDebug() << "Event Location:" << event_location;

    Event event(time_stamp, event_type, event_data, event_location);
    emit eventReceived(event);
}

void SimpleServer::on_client_data_received()
{
    QTcpSocket *client_socket = qobject_cast<QTcpSocket *>(sender());
    if (!client_socket)
        return;

    QDataStream in(client_socket);

    quint16 block_size;
    in >> block_size;

    if (client_socket->bytesAvailable() < block_size) {
        return;  // We don't have the complete data yet.
    }

    QDateTime time_stamp;
    QString event_type;
    QString event_data;
    QString event_location;
    in >> time_stamp >> event_type >> event_data >> event_location;

    qDebug() << "Received Event in SERVER from client:";
    qDebug() << "Timestamp:" << time_stamp;
    qDebug() << "Event Type:" << event_type;
    qDebug() << "Event Data:" << event_data;
    qDebug() << "Event Location:" << event_location;

    if(event_type == "ROOM_REQ") {
        int room_number = event_data.toInt();
        emit roomRequestReceived(room_number); // Emit the room request signal
        return;
    }

    // Optionally, handle any other client-specific event types as necessary.
}
