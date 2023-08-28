#ifndef SERVER_MANAGER_HPP
#define SERVER_MANAGER_HPP

#include <vector>
#include <memory>

#include "simple_server.hpp"
#include "room_handler.hpp"
#include "device_config.hpp"
#include "agent.hpp"
#include "event_from_server.hpp"

using namespace dashboard;

class ServerManager : public QObject 
{
    Q_OBJECT
public:
    ServerManager();
    void start_services();
    void EventRouter(const Event &event);

private slots:
    void handleReceivedEvent(const Event &event);

private:
    SimpleServer m_simple_server_instance; //TCP SERVER FOR SENSORS


private:
   std::map<int, RoomHandler> m_room_to_handlers_map;
};

#endif // SERVER_MANAGER_HPP
