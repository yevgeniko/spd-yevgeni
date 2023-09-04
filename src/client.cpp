#include "client.hpp"

namespace spd {

Client::Client() :
m_room_number {-1}
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
    if (is_abnormal(a_eventType))
    {
        qDebug() << "IN Client::handleNewData WITH ABNORMAL EVENT";
    } 
        Event e(a_timeStamp, a_eventType, a_eventData, a_eventLocation); // object dies?
        m_ui.add_event(e);

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
}

void Client::checkAndRequestRoomEvents()
{
    if (m_manager.get_is_connected() && m_room_number != -1)
    {
        requestRoomEvents();
    }
}

}