#ifndef CLIENT_HPP
#define CLIENT_HPP

#include <QString>
#include <memory>
#include "client_TCP.hpp"
#include "ui.hpp"
#include <QObject>

namespace spd {

class Client : public QObject {
    Q_OBJECT // <-- This macro is important

public:
    Client();

    void connect_to_server(const QString &address, quint16 port);

private slots:
    void handleNewData(QDateTime const& timeStamp, QString const& eventType, QString const& eventData, QString const& eventLocation);

private:
    ClientTCP m_manager;
    UI m_ui;
};

} // namespace spd

#endif //CLIENT_HPP
