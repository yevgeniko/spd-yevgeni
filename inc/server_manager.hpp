#ifndef SERVER_MANAGER_HPP
#define SERVER_MANAGER_HPP

#include <memory>
#include <QMap>
#include <QString>
#include <QDebug>
#include <QThread>

#include "simple_server.hpp"
#include "room_handler.hpp"
#include "device_config.hpp"
#include "agent.hpp"
#include "event_from_server.hpp"
#include "event.hpp"
#include "logger.hpp"

using namespace dashboard;

class EventHandlerBase;
class RoomHandler;

class ServerManager : public QObject 
{
    Q_OBJECT
public:
    ServerManager();
    void start_services();
    void EventRouter(const Event &event);
    void handleStopRequest();

private slots:
    void handleReceivedEvent(const Event &event);
    void handleRoomRequest(int room_number, QTcpSocket* clientSocket);
    
public slots:
    void addAlert(const Event& event);
    void updateEventToRoomMap(int room_number, const Event& event);

private:
    SimpleServer m_simple_server_instance;
    QMap<int, std::shared_ptr<RoomHandler>> m_room_to_handlers_map;
    QTcpSocket* m_current_client_socket = nullptr;  // Store the single client's socket
    int m_current_subscribed_room = -1;
    dashboard::Logger m_logger;

};

#endif // SERVER_MANAGER_HPP
