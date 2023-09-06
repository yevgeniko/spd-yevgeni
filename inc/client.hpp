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

    void connect_to_server(const QHostAddress &address, quint16 port);

private slots:
    void handleNewData(QDateTime const& timeStamp, QString const& eventType, QString const& eventData, QString const& eventLocation);

    void requestRoomEvents();
    void update_room_num(const int a_num);
    void checkAndRequestRoomEvents();

private:
    ClientTCP m_manager;
    UI m_ui;
    int m_room_number;
};

} // namespace spd

#endif //CLIENT_HPP
