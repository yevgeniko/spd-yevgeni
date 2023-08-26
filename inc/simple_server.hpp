#ifndef SIMPLE_SERVER_HPP
#define SIMPLE_SERVER_HPP

#include <QTcpServer>
#include <QTcpSocket>
#include <QCoreApplication>
#include <QDebug>
#include <QDataStream>
#include <QDateTime>

#include "event.hpp"


class SimpleServer : public QObject {
    Q_OBJECT

public:
    SimpleServer();
    void connectToClientManager(const QHostAddress &address, quint16 port);
    Event get_event() const;

private slots:
    void onNewConnection();
    void onDataReceived();


private:
    QTcpServer *server;
    QTcpSocket *forwardingSocket;
    //Event m_event;

};

#endif // SIMPLE_SERVER_HPP
