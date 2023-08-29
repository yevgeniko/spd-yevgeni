#ifndef SERVER_MANAGER_HPP
#define SERVER_MANAGER_HPP

#include <vector>
#include <memory>
#include <QMap>
#include <QQueue>
#include <QString>
#include <QDebug>

#include "simple_server.hpp"
#include "room_handler.hpp"
#include "device_config.hpp"
#include "agent.hpp"
#include "event_from_server.hpp"
#include "event.hpp"

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

private slots:
    void handleReceivedEvent(const Event &event);

public slots:
    void addAlert(const Event& event);
    void updateEventToRoomMap(int room_number, const Event& event);

private:
    SimpleServer m_simple_server_instance;

    QMap<int, std::shared_ptr<RoomHandler>> m_room_to_handlers_map;
    QMap<int, QQueue<Event>> m_event_to_room_map;
    QQueue<Event> m_alerts;
};

#endif // SERVER_MANAGER_HPP
