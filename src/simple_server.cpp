#include "simple_server.hpp"
#include "sensors.hpp"
#include "pulse_event_handler.hpp"

SimpleServer::SimpleServer()
//:m_event("dfdggg", "ggfgg", "fgffh")
{
    m_server.reset(new QTcpServer(this));
    m_forwarding_socket.reset(new QTcpSocket(this));

    connect(m_server.data(), &QTcpServer::newConnection, this, &SimpleServer::on_new_connection);
    connect(m_forwarding_socket.data(), &QTcpSocket::readyRead, this, &SimpleServer::on_request_received);
        if (!m_server->listen(QHostAddress::Any, 12345)) {
        qCritical() << "Server could not start!";
    } else {
        qDebug() << "Server started!";
    }
}

void SimpleServer::on_new_connection()
{
    QTcpSocket *client_socket = m_server->nextPendingConnection();
    // connect(m_forwarding_socket.data(), &QTcpSocket::readyRead, this, &SimpleServer::on_request_received);
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


    Event event(time_stamp, event_type, event_data, event_location);
    emit eventReceived(event);
    
}



void SimpleServer::connect_to_client_manager(const QHostAddress &address, quint16 port) 
{
    qDebug() << "Attempting to connect to ClientManager at" << address.toString() << "on port" << port;
    m_forwarding_socket->connectToHost(address, port);
}

// Event SimpleServer::get_event()
// {
//     Event event = m_events.front();
//     m_events.pop();
//     return event;
// }

void SimpleServer::forward_event_to_client(const Event& a_dequeued_Event)
{
    qDebug() << "enterd forward_event_to_client()";
    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);

    QDateTime time_stamp = a_dequeued_Event.getTimestamp();
    QString event_type = a_dequeued_Event.getEventType(); 
    QString event_data = a_dequeued_Event.getEventData();
    QString event_location = a_dequeued_Event.getEventLocation();


    out << (quint16)0;
    out << time_stamp << event_type << event_data << event_location;

    out.device()->seek(0);
    out << (quint16)(block.size() - sizeof(quint16));

    if(m_forwarding_socket->state() == QTcpSocket::ConnectedState) {
    m_forwarding_socket->write(block);
    } else {
        qDebug() << "Failed to forward data because m_forwarding_socket is not connected.";
    }
    qDebug() << "forward data" << event_type << event_data << '\n';
}

void SimpleServer::on_request_received()
{
    QTcpSocket *client_socket = qobject_cast<QTcpSocket *>(sender());
    if (!client_socket)
        return;

    QDataStream in(client_socket);
    quint16 block_size;
    in >> block_size;

    Request request;
    in >> request.request_type >> request.room_number;

    qDebug() << "Received Request from Client Manager:";
    qDebug() << "Room Number:" << request.room_number;
    
    emit requestReceived(request.room_number);
}
