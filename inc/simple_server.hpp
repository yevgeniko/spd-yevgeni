#ifndef SIMPLE_SERVER_HPP
#define SIMPLE_SERVER_HPP

#include <QTcpServer>
#include <QTcpSocket>
#include <QCoreApplication>
#include <QDebug>
#include <QDataStream>
#include <QDateTime>
#include <QScopedPointer>
#include "event.hpp"

class SimpleServer : public QObject
{
    Q_OBJECT

public:
    SimpleServer();
    void start_client_listener(const QHostAddress &a_address, quint16 a_port); 
    Event get_event() const;
    void forward_data(const QDateTime &time_stamp, const QString &event_type, const QString &event_data, const QString &event_location, QTcpSocket *socket);

private slots:
    void on_new_connection();
    void on_sensor_data_received();
    void on_client_data_received(); 
    void on_client_connected(); 

signals:
    void eventReceived(Event &event);
    void roomRequestReceived(int roomNumber, QTcpSocket* clientSocket);


private:
    QScopedPointer<QTcpServer> m_server;
    QScopedPointer<QTcpServer> m_client_server; 
    QScopedPointer<QTcpSocket> m_forwarding_socket;
    QMap<QTcpSocket*, quint16> m_blockSizeState;
    QMap<int, QTcpSocket*> m_pendingRequests;
};

#endif // SIMPLE_SERVER_HPP
