#include "simple_server.hpp"
#include "sensors.hpp"
#include "pulse_event_handler.hpp"

SimpleServer::SimpleServer()
//:m_event("dfdggg", "ggfgg", "fgffh")
{
    m_server.reset(new QTcpServer(this));
    m_forwarding_socket.reset(new QTcpSocket(this));

    connect(m_server.data(), &QTcpServer::newConnection, this, &SimpleServer::on_new_connection);
    if (!m_server->listen(QHostAddress::LocalHost, 12345)) {
        qCritical() << "Server could not start!";
    } else {
        qDebug() << "Server started!";
    }
}

void SimpleServer::on_new_connection()
{
    QTcpSocket *client_socket = m_server->nextPendingConnection();
    connect(client_socket, &QTcpSocket::readyRead, this, &SimpleServer::on_data_received);
    connect(client_socket, &QTcpSocket::disconnected, client_socket, &QTcpSocket::deleteLater);
}

void SimpleServer::on_data_received()
{
    QTcpSocket *client_socket = qobject_cast<QTcpSocket *>(sender());
    if (!client_socket)
        return;

    QDataStream in(client_socket);
    quint16 block_size;
    in >> block_size;

    QDateTime time_stamp;
    QString event_type;
    QString event_data;
    QString event_location;
    in >> time_stamp >> event_type >> event_data >> event_location;


    qDebug() << "Received Event in SERVER:";
    qDebug() << "Timestamp:" << time_stamp;
    qDebug() << "Event Type:" << event_type;
    qDebug() << "Event Data:" << event_data;
    qDebug() << "Event Location:" << event_location;

    // creating a signal for ServerManager that there is a new event
    Event event(time_stamp, event_type, event_data, event_location);
    emit eventReceived(event);

    // forwarding the data to the client manager - TODO make as function
    // QByteArray block;
    // QDataStream out(&block, QIODevice::WriteOnly);

    // out << (quint16)0;
    // out << timeStamp << eventType << eventData << eventLocation;

    // out.device()->seek(0);
    // out << (quint16)(block.size() - sizeof(quint16));

    if(forwardingSocket->state() == QTcpSocket::ConnectedState) {
    forwardingSocket->write(block);
    } else {
        qDebug() << "Failed to forward data because m_forwarding_socket is not connected.";
    }

}

void SimpleServer::connectToClientManager(const QHostAddress &address, quint16 port) {
    qDebug() << "Attempting to connect to ClientManager at" << address.toString() << "on port" << port;
    forwardingSocket->connectToHost(address, port);
}

Event SimpleServer::get_event()
{
    Event event = m_events.front();
    m_events.pop();
    return event;
}

void SimpleServer::forward_event_to_client()
{
    
    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);


    if (roomEventQueues.find(room_number) != roomEventQueues.end() && !roomEventQueues[room_number].empty()) {
        Event dequeued_Event = roomEventQueues[room_number].front();
        roomEventQueues[room_number].pop();
    }

    QDateTime timeStamp = dequeued_Event.getTimestamp();
    QString eventType = dequeued_Event.getEventType(); 
    QString eventData = dequeued_Event.getEventData();
    QString eventLocation = dequeued_Event.getEventLocation();


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

void SimpleServer::connect_to_client_manager(const QHostAddress &a_address, quint16 a_port) {
    qDebug() << "Attempting to connect to ClientManager at" << a_address.toString() << "on port" << a_port;
    m_forwarding_socket->connectToHost(a_address, a_port);
}

// Event SimpleServer::get_event() const
// {
//     return m_event;
// }
