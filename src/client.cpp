#include "client.hpp"

#include "event.hpp"
#include <QDateTime>

namespace spd {

Client::Client()
{
    connect(&m_manager, &ClientTCP::newDataReceived, this, &Client::handleNewData);
    connect(&m_ui, &UI::set_room_num, this, &Client::update_room_num);
    QDateTime currentDateTime = QDateTime::currentDateTime();
    Event e(currentDateTime, "a_eventType", "a_eventData", "a_eventLocation");
    Event e1(currentDateTime, "a_eventType", "a_eventData", "a_eventLocation");
    m_ui.add_event(e);
    m_ui.add_event(e1);
}

void Client::connect_to_server(const QString &a_address, quint16 a_port) 
{
    m_manager.startListening(a_address, a_port);
    interval_requests();
}

void Client::handleNewData(QDateTime const& a_timeStamp, QString const& a_eventType, QString const& a_eventData, QString const& a_eventLocation) 
{
    Event e(a_timeStamp, a_eventType, a_eventData, a_eventLocation);
    m_ui.add_event(e);
}


void Client::interval_requests()
{
    m_request_timer = std::make_unique<QTimer>();
    connect(m_request_timer.get(), &QTimer::timeout, this, &Client::create_requests);

    m_request_timer->start(1000);
}

void Client::create_requests()
{
        Request request;
        request.request_type = "Send Data";
        request.room_number = m_roomn;

        m_manager.send_request(request);
        qDebug() << "created request\n";    
}

void Client::update_room_num(int num)
{
    qDebug() << "1\n";
    m_roomn = num;
}

// connect(&clientManagerInstance, &ClientManager::newDataReceived, this, [&](QDateTime timeStamp, QString eventType, QString eventData, QString eventLocation) {
//     // Handle the data in the Client, e.g., update the UI.
// });

}