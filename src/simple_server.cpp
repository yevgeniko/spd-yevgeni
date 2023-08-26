#include "simple_server.hpp"

SimpleServer::SimpleServer()
//:m_event("dfdggg", "ggfgg", "fgffh")
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

    // Event event(eventType, eventData, eventLocation);
    // m_event = std::move(event);

    qDebug() << "Received Event in SERVER:";
    qDebug() << "Timestamp:" << timeStamp;
    qDebug() << "Event Type:" << eventType;
    qDebug() << "Event Data:" << eventData;
    qDebug() << "Event Location:" << eventLocation;

    // forwarding the data to the client manager - TODO make as function
    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);

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

void SimpleServer::connectToClientManager(const QHostAddress &address, quint16 port) {
    qDebug() << "Attempting to connect to ClientManager at" << address.toString() << "on port" << port;
    forwardingSocket->connectToHost(address, port);
}

// Event SimpleServer::get_event() const
// {
//     return m_event;
// }

