#ifndef SIMPLE_SERVER_HPP
#define SIMPLE_SERVER_HPP

#include <QTcpServer>
#include <QTcpSocket>
#include <QCoreApplication>
#include <QDebug>
#include <QDataStream>
#include <QDateTime>

#include <queue>

#include "event.hpp"


class SimpleServer : public QObject {
    Q_OBJECT

public:
    SimpleServer();
    void connectToClientManager(const QHostAddress &address, quint16 port);
    void forward_event_to_client();
    Event get_event();

private slots:
    void onNewConnection();
    void onDataReceived();


private:
    QTcpServer *server;
    QTcpSocket *forwardingSocket;   
    std::queue<Event> m_events;
};

#endif // SIMPLE_SERVER_HPP
