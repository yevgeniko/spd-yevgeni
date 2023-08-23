#ifndef CLIENT_SERVER_MANAGER_HPP
#define CLIENT_MANAGER_HPP

#include <QObject>
#include <QList>
#include <QTcpSocket>
#include <QDataStream>
#include <QDateTime>
#include <memory>
#include "client.hpp"

namespace spd {
class ClientManager : public QObject {

    Q_OBJECT

public:
    ClientManager();
    ~ClientManager();

    ClientManager(ClientManager const& a_other) = delete;
    ClientManager& operator=(ClientManager const& a_other) = delete;

    void connect_to_server(const QString &address, quint16 port);
    //void send_to_data_server();
    // void receive_event_from_server();

    // void register_device();

private slots:
    void onDataReceived();
    void onNewConnection();

private:
    std::unique_ptr<QTcpSocket> m_socket;
    quint16 m_block_size;
};

} // namespace name

#endif //CLIENT_SERVER_MANAGER_HPP
