#include "client.hpp"

namespace spd {

Client::Client()
{
}

void Client::connect_to_server(const QString &address, quint16 port) 
{
    m_manager.connect_to_server(address, port);
}

// connect(&clientManagerInstance, &ClientManager::newDataReceived, this, [&](QDateTime timeStamp, QString eventType, QString eventData, QString eventLocation) {
//     // Handle the data in the Client, e.g., update the UI.
// });

}