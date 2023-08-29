#include "client.hpp"

namespace spd {

Client::Client()
{
    connect(&m_manager, &ClientTCP::newDataReceived, this, &Client::handleNewData);
}

void Client::connect_to_server(const QString &address, quint16 port) 
{
    m_manager.startListening(address, port);
    interval_requests();
}

void Client::handleNewData(QDateTime const& timeStamp, QString const& eventType, QString const& eventData, QString const& eventLocation) 
{
    m_ui.show_event(timeStamp, eventType, eventData, eventLocation);
}


void Client::interval_requests()
{
    m_request_timer = std::make_unique<QTimer>();
    connect(m_request_timer.get(), &QTimer::timeout, this, &Client::create_requests);

    m_request_timer->start(1000);
}

void Client::create_requests()
{
    while (true) {
        Request request;
        request.request_type = "Send Data";
        request.room_number = 1;

        m_manager.send_request(request);

        QThread::msleep(1000); 
    }
}

// connect(&clientManagerInstance, &ClientManager::newDataReceived, this, [&](QDateTime timeStamp, QString eventType, QString eventData, QString eventLocation) {
//     // Handle the data in the Client, e.g., update the UI.
// });

}