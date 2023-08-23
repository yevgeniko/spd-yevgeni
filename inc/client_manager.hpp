#ifndef CLIENT_MANAGER_HPP
#define CLIENT_MANAGER_HPP

#include <QObject>
#include <QList>
#include <QTcpServer>
#include <QTcpSocket>
#include <QDataStream>
#include <QDateTime>
#include <memory>

namespace spd {

class Client; // forward declaration

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
signals:
    void newDataReceived(QDateTime, QString, QString, QString);

private slots:
    void onDataReceived();
    void onNewConnection();

private:
    std::unique_ptr<QTcpSocket> m_socket;
    quint16 m_block_size;
    QTcpServer *serverListener;
    QTcpSocket *incomingSocket;
};

} // namespace name

#endif //CLIENT_MANAGER_HPP