#include "server_manager.hpp"
#include "room_handler.hpp"
#include "pulse_event_handler.hpp"

ServerManager::ServerManager()
{
    connect(&m_simple_server_instance, &SimpleServer::eventReceived, this, &ServerManager::handleReceivedEvent);
    connect(&m_simple_server_instance, &SimpleServer::roomRequestReceived, this, &ServerManager::handleRoomRequest);
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

    // Handling Pulse Events
    if (sensor_type == "PULSE")
    {
        if (!handlers->get_pulse_handler_flag()) {
            connect(handlers->pulseHandler.get(), &PulseEventHandler::alertGenerated, this, &ServerManager::addAlert);
            connect(handlers->pulseHandler.get(), &PulseEventHandler::eventProcessed, this, &ServerManager::updateEventToRoomMap);
            handlers->set_pulse_handler_flag(true);
        }
        handlers->pulseHandler->handleEvent(event);
    }

    // Handling BloodPressure Events
    if (sensor_type == "BP")
    {
        if (!handlers->get_bloodpressure_handler_flag()) {
            connect(handlers->bloodPressureHandler.get(), &BloodPressureEventHandler::alertGenerated, this, &ServerManager::addAlert);
            connect(handlers->bloodPressureHandler.get(), &BloodPressureEventHandler::eventProcessed, this, &ServerManager::updateEventToRoomMap);
            handlers->set_bloodpressure_handler_flag(true);
        }
        handlers->bloodPressureHandler->handleEvent(event);
    }

    // Handling Saturation Events
    if (sensor_type == "SAT")
    {
        if (!handlers->get_saturation_handler_flag()) {
            connect(handlers->saturationHandler.get(), &SaturationEventHandler::alertGenerated, this, &ServerManager::addAlert);
            connect(handlers->saturationHandler.get(), &SaturationEventHandler::eventProcessed, this, &ServerManager::updateEventToRoomMap);
            handlers->set_saturation_handler_flag(true);
        }
        handlers->saturationHandler->handleEvent(event);
    }

    // Handling Temperature Events
    if (sensor_type == "TEMP")
    {
        if (!handlers->get_temperature_handler_flag()) {
            connect(handlers->temperatureHandler.get(), &TemperatureEventHandler::alertGenerated, this, &ServerManager::addAlert);
            connect(handlers->temperatureHandler.get(), &TemperatureEventHandler::eventProcessed, this, &ServerManager::updateEventToRoomMap);
            handlers->set_temperature_handler_flag(true);
        }
        handlers->temperatureHandler->handleEvent(event);
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

    forwardProcessedEventToSubscribers(room_number, event);
}



void ServerManager::handleRoomRequest(int room_number, QTcpSocket* clientSocket)
{
    // If the client is already subscribed to another room, remove it from that room's list of subscribers
    if (m_client_to_room_map.contains(clientSocket)) {
        int previousRoom = m_client_to_room_map[clientSocket];
        m_subscribed_clients[previousRoom].removeOne(clientSocket);  // remove the client from the old room's list
    }
    
    // Update the client's current room
    m_client_to_room_map[clientSocket] = room_number;
    
    // Add the client to the new room's list of subscribers
    if (!m_subscribed_clients.contains(room_number)) {
        m_subscribed_clients[room_number] = QList<QTcpSocket*>();
    }
    
    m_subscribed_clients[room_number].append(clientSocket);
}

void ServerManager::handleStopRequest()
{
    m_current_subscribed_room = -1;
}


void ServerManager::forwardProcessedEventToSubscribers(int room_number, const Event &event)
{
    Q_UNUSED(event);

    if (m_event_to_room_map.contains(room_number)) {
        Event storedEvent = m_event_to_room_map[room_number].dequeue();

        if (m_subscribed_clients.contains(room_number)) {
            QList<QTcpSocket*>& subscribers = m_subscribed_clients[room_number];

            for (QTcpSocket* subscriber : subscribers) {
                if (subscriber->state() == QTcpSocket::ConnectedState) {
                    m_simple_server_instance.forward_data(storedEvent.getTimestamp(), storedEvent.getEventType(), storedEvent.getEventData(), storedEvent.getEventLocation(), subscriber);
                }
            }
        }
    }
}
