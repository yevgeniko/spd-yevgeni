#ifndef SERVER_MANAGER_HPP
#define SERVER_MANAGER_HPP

#include "simple_server.hpp"

class ServerManager : public QObject {
    Q_OBJECT
public:
    ServerManager();
    void start_services();

private:
    SimpleServer m_simple_server_instance; //TCP SERVER FOR SENSORS
};

#endif // SERVER_MANAGER_HPP
