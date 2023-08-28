#include "server_manager.hpp"
#include "room_handler.hpp"
#include "pulse_event_handler.hpp"

ServerManager::ServerManager()
{
    m_simple_server_instance.connect_to_client_manager(QHostAddress::LocalHost, 5555); //random port
    connect(&m_simple_server_instance, &SimpleServer::eventReceived, this, &ServerManager::handleReceivedEvent);
}


void ServerManager::start_services()
{
    // ALL SERVER TASKS GO HERE
    // simpleServer is already started in ctor

}

void ServerManager::handleReceivedEvent(const Event &event)
{
    EventRouter(event);
}

void ServerManager::EventRouter(const Event &event)
{
    // extraction of room number and sensor type from the event.
    int room_number = event.getEventLocation().toInt();
    QString sensor_type = event.getEventType();

    RoomHandler &handlers = m_room_to_handlers_map[room_number];

    if (sensor_type == "Pulse")
    {
        handlers.pulseHandler->handleEvent(event);
    }
    // else if (sensorType == "BloodPressure")
    // {
    //     handlers.pulseHandler->handleEvent(event);
    // }

    //other sensor types as needed.
}