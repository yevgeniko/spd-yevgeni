#include "server_manager.hpp"
#include "room_handler.hpp"
#include "pulse_event_handler.hpp"

ServerManager::ServerManager() :
m_logger("log_file")
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
    m_logger.log_event(event);
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
    if (m_current_client_socket && m_current_client_socket->state() == QTcpSocket::ConnectedState) 
    {
        // m_simple_server_instance.forward_data(event.getTimestamp(), event.getEventType(), event.getEventData(), event.getEventLocation(), m_current_client_socket);
        // QThread::msleep(50);
    }
}


void ServerManager::updateEventToRoomMap(int room_number, const Event& event) 
{
    qDebug() << "enqueued to event_to_room_map : " << event.getEventData();
    m_event_to_room_map[room_number].enqueue(event);
}
    //other sensor types as needed.



void ServerManager::send_event(int room_number) 
{
    while(!m_event_to_room_map.value(room_number).empty()){
        if (m_event_to_room_map.contains(room_number)) {
            Event dequeued_Event = m_event_to_room_map[room_number].dequeue();
            qDebug() << " sent event" << dequeued_Event.getEventType() << dequeued_Event.getEventType() << '\n'; 
            m_simple_server_instance.forward_event_to_client(dequeued_Event);
        }else{
            qDebug() << " sent event function: not found. sending other one.  ";
            
            QString eventType = "ERROR";  
            QString eventData = "0"; 
            QString eventLocation = "NoWhere";  

            QDateTime timestamp = QDateTime::currentDateTime();  

            Event newEvent(timestamp, eventType, eventData, eventLocation);

            m_simple_server_instance.forward_event_to_client(newEvent);
        }
    }
    if (!m_alerts.isEmpty()) {
        Event alert_event = m_alerts.dequeue();
        m_simple_server_instance.forward_event_to_client(alert_event);
    }
    m_alerts.clear();

}

void ServerManager::handleRoomRequest(int room_number, QTcpSocket* clientSocket)
{
    m_current_client_socket = clientSocket;
    m_current_subscribed_room = room_number;
}

void ServerManager::handleStopRequest()
{
    m_current_subscribed_room = -1;
}


