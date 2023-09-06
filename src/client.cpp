#include "client.hpp"
#include <chrono>
#include <thread>
#include "const_and_enums.hpp"

namespace spd {

Client::Client() 
: m_room_number {-1}
, m_hash_type{{"",0}}
{
    connect(&m_manager, &ClientTCP::newDataReceived, this, &Client::handleNewData);
    connect(&m_ui, &UI::set_room_num, this, &Client::update_room_num);
}

void Client::connect_to_server(const QHostAddress &address, quint16 port) 
{
    m_manager.connectToServer(address, port);
}


void Client::handleNewData(QDateTime const& a_timeStamp, QString const& a_eventType, QString const& a_eventData, QString const& a_eventLocation) 
{
    Event e(a_timeStamp, a_eventType, a_eventData, a_eventLocation);
    if (is_abnormal(a_eventType)) {

        qDebug() << "IN Client::handleNewData WITH ABNORMAL EVENT";
        
        size_t postition = is_new_abnormal(e);

        if(postition == 0) {
            m_start_time = std::chrono::high_resolution_clock::now();
            m_ui.add_abnorml_event(e);
        } else {
            m_ui.update_abnorml_event(e, postition - 1);
        }
    } else {
        if(is_new_type(a_eventType)) {
            m_ui.add_event(e);
        } else {
            m_ui.update_event(e, m_hash_type[a_eventType]);
        }
        m_ui.add_event(e);
    }
    if(is_timer_ended()) {
        m_list_abnormal.clear();
    }
} 


void Client::requestRoomEvents()
{
    qDebug() << "IN Client::requestRoomEvents ";
    if (m_room_number != -1) {
        QDateTime currentTime = QDateTime::currentDateTime();
        Event requestEvent(currentTime, "ROOM_REQ", QString::number(m_room_number), "");
        m_manager.sendRoomRequest(requestEvent);
    }
}

void Client::update_room_num(const int a_num)
{
    m_room_number = a_num;
    checkAndRequestRoomEvents();
    if(m_room_number == 0 && !m_hash_type.empty()) {
        m_hash_type.clear();
    }
}

void Client::checkAndRequestRoomEvents()
{
    if (m_manager.get_is_connected() && m_room_number != -1)
    {
        requestRoomEvents();
    }
}

bool Client::is_new_type(QString const& a_type)
{
    if(m_hash_type.count(a_type)) {
        return false;
    } else {
        m_hash_type[a_type] = m_hash_type.size();
        return true;
    }
}

size_t spd::Client::is_new_abnormal(Event const &a_abnormal)
{
    size_t posistion = 0;
    for(const auto &event: m_list_abnormal) {
        ++posistion;
        if(event.getEventLocation() == a_abnormal.getEventLocation() && event.getEventType() == a_abnormal.getEventType()) {
            return posistion;
        }
    }
    return posistion;
}

bool Client::is_timer_ended()
{
    auto end_time = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::seconds>(end_time - m_start_time);

    if (duration.count() >= MAX_ABNORMAL_DURATION) {
        return true;
    }
    return false;
}

}
