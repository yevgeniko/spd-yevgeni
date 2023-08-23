#include "simple_server.hpp"

SimpleServer::SimpleServer()
{
    server = new QTcpServer(this);

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

    qDebug() << "Received Event:";
    qDebug() << "Timestamp:" << timeStamp;
    qDebug() << "Event Type:" << eventType;
    qDebug() << "Event Data:" << eventData;
    qDebug() << "Event Location:" << eventLocation;
}
