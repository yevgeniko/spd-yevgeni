#include "server_manager.hpp"
#include "room_handler.hpp"
#include "pulse_event_handler.hpp"

ServerManager::ServerManager()
{
    connect(&m_simple_server_instance, &SimpleServer::eventReceived, this, &ServerManager::handleReceivedEvent);
    connect(&m_simple_server_instance, &SimpleServer::roomRequestReceived, this, &ServerManager::handleRoomRequest);
    m_event_polling_timer = new QTimer(this);
    connect(m_event_polling_timer, &QTimer::timeout, this, &ServerManager::pollEvents);
    m_event_polling_timer->start(1000);
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


void ServerManager::handleRoomRequest(int room_number) {
    m_current_subscribed_room = room_number;
}

void ServerManager::handleStopRequest()
{
    m_current_subscribed_room = -1;
}

void ServerManager::pollEvents()
{
    if (m_current_subscribed_room == -1) return;

    if (m_event_to_room_map.contains(m_current_subscribed_room)) {
        QQueue<Event>& roomEvents = m_event_to_room_map[m_current_subscribed_room];
        
        while (!roomEvents.isEmpty()) {
            Event e = roomEvents.dequeue();
            m_simple_server_instance.forward_data(e.getTimestamp(), e.getEventType(), e.getEventData(), e.getEventLocation());
        }
    }
}