#include "server_manager.hpp"

ServerManager::ServerManager()
{
    m_simple_server_instance.connectToClientManager(QHostAddress::LocalHost, 5555); //random port
}

void ServerManager::start_services()
{
    // ALL SERVER TASKS GO HERE
    // simpleServer is already started in ctor

}
