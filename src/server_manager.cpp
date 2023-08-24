#include "server_manager.hpp"

ServerManager::ServerManager()
:m_device_config("devices.ini")
{
    create_devices();
    m_simple_server_instance.connectToClientManager(QHostAddress::LocalHost, 5555); //random port
}

void ServerManager::create_devices()
{
    for (const DeviceStruct& device_info : m_device_config.m_devices) {
        std::unique_ptr<Agent> device = std::make_unique<Agent>(device_info.device_ID,
            device_info.type, device_info.room, device_info.configuration);
        m_device_pointers.push_back(std::move(device));
    }
}

const std::vector<std::unique_ptr<Agent>>& ServerManager::server_devices() const {
    return m_device_pointers;
}

void ServerManager::start_services()
{
    // ALL SERVER TASKS GO HERE
    // simpleServer is already started in ctor

}

void ServerManager::connect_to_agent() 
{
    Event event = m_simple_server_instance.get_event();
    
    for (auto& agent : m_agents_pointers) {
        if (event.getSenderID() == agent->getAgentID()) {
            ProcessResult response = agent->procces_event(event);
            break;
        }
    }
    if (response == ProcessResult::ConfigurationSent){
        m_simple_server_instance.send_configoration(agent->getAgentID(), agent->getConfiguration());
        // need to write send_configoration() function in SimpleServerClass
    }
    else if(response == ProcessResult::RegularMessage){
        m_simple_server_instance.send_to_client(agent->agent_event());
        // need to write agent_event() finction in Agent Class.
        // it will return a differnt kind of event and will send it to the client.
        // need to write send_to_client() function in SimpleServerClass
    }
}