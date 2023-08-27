#include "client.hpp"

namespace spd {

Client::Client()
{
    connect(&m_manager, &ClientTCP::newDataReceived, this, &Client::handleNewData);
}

void Client::connect_to_server(const QString &address, quint16 port) 
{
    m_manager.startListening(address, port);
}

void Client::handleNewData(QDateTime const& timeStamp, QString const& eventType, QString const& eventData, QString const& eventLocation) 
{
    m_ui.show_event(timeStamp, eventType, eventData, eventLocation);
}


// connect(&clientManagerInstance, &ClientManager::newDataReceived, this, [&](QDateTime timeStamp, QString eventType, QString eventData, QString eventLocation) {
//     // Handle the data in the Client, e.g., update the UI.
// });

}