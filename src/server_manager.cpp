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
    int room_number = event.getEventLocation().toInt();
    QString sensor_type = event.getEventType();

    if (!m_room_to_handlers_map.contains(room_number))
    {
        m_room_to_handlers_map[room_number] = std::make_shared<RoomHandler>();
    }

    std::shared_ptr<RoomHandler>& handlers = m_room_to_handlers_map[room_number];

    if (sensor_type == "Pulse")
    {
        if (!m_room_to_handlers_map[room_number]->get_pulse_handler_flag())
        {
            connect(handlers->pulseHandler.get(), &PulseEventHandler::alertGenerated, this, &ServerManager::addAlert);
            connect(handlers->pulseHandler.get(), &PulseEventHandler::eventProcessed, this, &ServerManager::updateEventToRoomMap);
            m_room_to_handlers_map[room_number]->set_pulse_handler_flag(true);
        }
        handlers->pulseHandler->handleEvent(event);
    }

}

void ServerManager::addAlert(const Event& event) 
{
    qDebug() << "enqueued to alerts: " << event.getEventData();
    m_alerts.enqueue(event);
}

void ServerManager::updateEventToRoomMap(int room_number, const Event& event) 
{
    qDebug() << "enqueued to event_to_room_map : " << event.getEventData();
    m_event_to_room_map[room_number].enqueue(event);
}
