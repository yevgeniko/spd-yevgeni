#ifndef CLIENT_HPP
#define CLIENT_HPP

#include <QString>
#include <memory>
#include <QObject>
#include <QThread>
#include <QTimer>
#include <QHash>

#include "event.hpp"
#include "client_TCP.hpp"
#include "ui.hpp"


namespace spd {

struct CustomEventComparator {
    bool operator()(Event const& a_first, Event const& a_second) const {
        if(a_first.getEventType() == a_second.getEventType() && a_first.getEventLocation() == a_second.getEventLocation()){
            return true;
        }
        return false;
    }
};

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
    bool is_new_type(QString const& a_type);
    size_t is_new_abnormal(Event const& a_abnormal);
    bool is_timer_ended();

private:
    ClientTCP m_manager;
    UI m_ui;
    int m_room_number;
    QHash<QString,size_t> m_hash_type;
    QList<Event> m_list_abnormal;
    std::chrono::_V2::system_clock::time_point m_start_time;
};



} // namespace spd

#endif //CLIENT_HPP
