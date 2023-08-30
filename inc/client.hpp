#ifndef CLIENT_HPP
#define CLIENT_HPP

#include <QString>
#include <memory>
#include "client_TCP.hpp"
#include "ui.hpp"
#include <QObject>
#include <QThread>
#include <QTimer>

namespace spd {

class Client : public QObject {
    Q_OBJECT

public:
    Client();

    void connect_to_server(const QString &a_address, quint16 a_port);
    void create_requests();
    void interval_requests();

private slots:
    void handleNewData(QDateTime const& a_timeStamp, QString const& a_eventType, QString const& a_eventData, QString const& a_eventLocation);

private:
    ClientTCP m_manager;
    UI m_ui;
    std::unique_ptr<QTimer> m_request_timer;
};

} // namespace spd

#endif //CLIENT_HPP
