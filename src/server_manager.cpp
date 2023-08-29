#include "server_manager.hpp"
#include "room_handler.hpp"
#include "pulse_event_handler.hpp"

ServerManager::ServerManager()
{
    m_simple_server_instance.connect_to_client_manager(QHostAddress::LocalHost, 5555); //random port
    connect(&m_simple_server_instance, &SimpleServer::eventReceived, this, &ServerManager::handleReceivedEvent);
    connect(&m_simple_server_instance, &SimpleServer::requestReceived, this, &ServerManager::send_event);
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


void ServerManager::send_event(int room_number) 
{
    if (m_event_to_room_map.contains(room_number) && !m_event_to_room_map.value(room_number).empty()) {
        Event dequeued_Event = m_event_to_room_map[room_number].dequeue();
        m_simple_server_instance.forward_event_to_client(dequeued_Event);
    }
}


