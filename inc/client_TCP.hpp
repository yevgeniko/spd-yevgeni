#ifndef CLIENT_TCP
#define CLIENT_TCP

#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>
#include <QDataStream>
#include <QDateTime>
#include <QPointer>
#include <memory>

#include "event.hpp"

namespace spd {

class ClientTCP : public QObject
{
    Q_OBJECT

public:
    ClientTCP();
    ~ClientTCP();

    ClientTCP(ClientTCP const& a_other) = delete;
    ClientTCP& operator=(ClientTCP const& a_other) = delete;

    void startListening(const QString &address, quint16 port);
    void send_request(const Request& a_request);

signals:
    void newDataReceived(QDateTime, QString, QString, QString);

private slots:
    void onNewConnection();
    void onDataReceived();

private:
    std::unique_ptr<QTcpServer> m_server;
    QPointer<QTcpSocket> m_socket;
};

} // namespace spd

#endif //CLIENT_TCP
