#ifndef SIMPLE_SERVER_HPP
#define SIMPLE_SERVER_HPP

#include <QTcpServer>
#include <QTcpSocket>
#include <QCoreApplication>
#include <QDebug>
#include <QDataStream>
#include <QDateTime>

class SimpleServer : public QObject {
    Q_OBJECT

public:
    SimpleServer();
    void connectToClientManager(const QHostAddress &address, quint16 port);

private slots:
    void onNewConnection();
    void onDataReceived();


private:
    QTcpServer *server;
    QTcpSocket *forwardingSocket;

};

#endif // SIMPLE_SERVER_HPP
