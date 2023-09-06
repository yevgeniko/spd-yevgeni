#include "server_manager.hpp"
#include "room_handler.hpp"
#include "pulse_event_handler.hpp"
#include "ai.hpp"

ServerManager::ServerManager() :
m_logger("log_file")
{
    connect(&m_simple_server_instance, &SimpleServer::eventReceived, this, &ServerManager::handleReceivedEvent);
    connect(&m_simple_server_instance, &SimpleServer::roomRequestReceived, this, &ServerManager::handleRoomRequest);
    connect(&m_ai, &AI::predictionReady, this, &ServerManager::handleAIPrediction);
}


void ServerManager::start_services()
{
    // ALL SERVER TASKS GO HERE
    // simpleServer is already started in ctor

}

void ServerManager::handleReceivedEvent(const Event &event)
{
    m_logger.log_event(event);
    m_ai.buffer_event(event);
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
        //m_ai.func(location, data)
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
    if (m_current_subscribed_room == room_number && m_current_client_socket && m_current_client_socket->state() == QTcpSocket::ConnectedState) 
    {
        m_simple_server_instance.forward_data(event.getTimestamp(), event.getEventType(), event.getEventData(), event.getEventLocation(), m_current_client_socket);
    }
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


void ServerManager::handleAIPrediction(int prediction, int room)
{
    QString predictionStr;
    if (prediction == 0) {
        predictionStr = "LOW RISK";
    } else if (prediction == 1) {
        predictionStr = "MEDIUM RISK";
    } else if (prediction == 2) {
        predictionStr = "HIGH RISK";
    }

    QDateTime current = QDateTime::currentDateTime();
    QString roomStr = QString::number(room);

    Event ai_event(current, "AI_EVENT", predictionStr, roomStr);
    m_simple_server_instance.forward_data(ai_event.getTimestamp(), ai_event.getEventType(), ai_event.getEventData(), ai_event.getEventLocation(), m_current_client_socket);

}

