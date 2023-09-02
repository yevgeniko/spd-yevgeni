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

void ServerManager::handleReceivedEvent(Event &event)
{
    EventRouter(event);
}


void ServerManager::EventRouter(Event &event)
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
        if (!m_room_to_handlers_map[room_number]->get_pulse_handler_flag()) {
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

    forwardAlertToAllSubscribers(event);
}


void ServerManager::updateEventToRoomMap(int room_number, const Event& event) 
{
    qDebug() << "enqueued to event_to_room_map : " << event.getEventData();
    m_event_to_room_map[room_number].enqueue(event);

    forwardProcessedEventToSubscribers(room_number, event);
}



void ServerManager::handleRoomRequest(int room_number, QTcpSocket* clientSocket)
{
    if (m_client_to_room_map.contains(clientSocket)) {
        int previousRoom = m_client_to_room_map[clientSocket];
        m_subscribed_clients[previousRoom].removeOne(clientSocket);
    }
    

    m_client_to_room_map[clientSocket] = room_number;
    

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


QList<QTcpSocket*> ServerManager::getAllUniqueClients()
{
    QSet<QTcpSocket*> uniqueClients;

    for(const auto& roomSubscribers : m_subscribed_clients)
    {
        for(QTcpSocket* subscriber : roomSubscribers)
        {
            uniqueClients.insert(subscriber);
        }
    }

    return uniqueClients.toList();
}

void ServerManager::forwardAlertToAllSubscribers(const Event &event)
{
    QList<QTcpSocket*> allClients = getAllUniqueClients();

    for(QTcpSocket* client : allClients)
    {
        if(client->state() == QTcpSocket::ConnectedState)
        {
            m_simple_server_instance.forward_data(event.getTimestamp(), event.getEventType(), event.getEventData(), event.getEventLocation(), client);
        }
    }
}
