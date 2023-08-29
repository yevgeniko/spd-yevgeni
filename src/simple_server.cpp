#include "simple_server.hpp"

SimpleServer::SimpleServer()
{
    server = new QTcpServer(this);
    forwardingSocket = new QTcpSocket(this);


    connect(server, &QTcpServer::newConnection, this, &SimpleServer::onNewConnection);
    if (!server->listen(QHostAddress::LocalHost, 12345)) {
        qCritical() << "Server could not start!";
    } else {
        qDebug() << "Server started!";
    }
}

void SimpleServer::onNewConnection()
{
    QTcpSocket *clientSocket = server->nextPendingConnection();
    connect(clientSocket, &QTcpSocket::readyRead, this, &SimpleServer::onDataReceived);
    connect(clientSocket, &QTcpSocket::disconnected, clientSocket, &QTcpSocket::deleteLater);
}

void SimpleServer::onDataReceived()
{
    QTcpSocket *clientSocket = qobject_cast<QTcpSocket *>(sender());
    if (!clientSocket)
        return;

    QDataStream in(clientSocket);
    quint16 blockSize;
    in >> blockSize;

    QDateTime timeStamp;
    QString eventType;
    QString eventData;
    QString eventLocation;
    in >> timeStamp >> eventType >> eventData >> eventLocation;

    m_events.emplace(eventType, eventData, eventLocation);

    qDebug() << "Received Event in SERVER:";
    qDebug() << "Timestamp:" << timeStamp;
    qDebug() << "Event Type:" << eventType;
    qDebug() << "Event Data:" << eventData;
    qDebug() << "Event Location:" << eventLocation;

    // forwarding the data to the client manager - TODO make as function
    // QByteArray block;
    // QDataStream out(&block, QIODevice::WriteOnly);

    // out << (quint16)0;
    // out << timeStamp << eventType << eventData << eventLocation;

    // out.device()->seek(0);
    // out << (quint16)(block.size() - sizeof(quint16));

    // if(forwardingSocket->state() == QTcpSocket::ConnectedState) {
    // forwardingSocket->write(block);
    // } else {
    //     qDebug() << "Failed to forward data because forwardingSocket is not connected.";
    // }

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
    out << timeStamp << eventType << eventData << eventLocation;

    out.device()->seek(0);
    out << (quint16)(block.size() - sizeof(quint16));

    if(forwardingSocket->state() == QTcpSocket::ConnectedState) {
    forwardingSocket->write(block);
    } else {
        qDebug() << "Failed to forward data because forwardingSocket is not connected.";
    }

}
