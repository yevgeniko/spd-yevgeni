
#ifndef CLIENT_TCP_HPP
#define CLIENT_TCP_HPP

#include <QTcpSocket>
#include <QCoreApplication>
#include <QDebug>
#include <QDataStream>
#include <QDateTime>
#include <QHostAddress>
#include "event.hpp"

class ClientTCP : public QObject
{
    Q_OBJECT

public:
    ClientTCP();

    ClientTCP(ClientTCP const& a_other) = delete;
    ClientTCP& operator=(ClientTCP const& a_other) = delete;

    void connectToServer(const QHostAddress &a_address, quint16 a_port);

    void sendRoomRequest(const Event &requestEvent);
    bool get_is_connected();

signals:
    void newDataReceived(QDateTime, QString, QString, QString);

    // void initialRoomRequestReady();

private slots:
    void on_data_received();
    void on_connected();
    void on_disconnected();

    // void requestInitialRoomEvents();


private:
    QScopedPointer<QTcpSocket> m_socket;
    bool m_is_connected;
};

#endif // CLIENT_TCP_HPP
