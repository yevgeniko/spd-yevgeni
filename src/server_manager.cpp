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
        m_agents_pointers.push_back(std::move(device));
    }
}

const std::vector<std::unique_ptr<Agent>>& ServerManager::server_devices() const {
    return m_agents_pointers;
}

void ServerManager::start_services()
{
    // ALL SERVER TASKS GO HERE
    // simpleServer is already started in ctor

}

void ServerManager::connect_to_agent() 
{
    Event event = m_simple_server_instance.get_event();
    // ProcessResult response;
    std::unique_ptr<Agent> agent = nullptr;
    
    for (auto& agent_ptr : m_agents_pointers) {
        if (event.getSenderID() == agent_ptr->getAgentID()) {
            agent = std::move(agent_ptr); 
            break;
        }
    }
    if (agent) {
            ProcessResult response = agent->process_event(event);
        if (response == ProcessResult::ConfigurationSent){
            m_simple_server_instance.send_configoration(agent->getAgentID(), agent->getConfiguration());
            // need to write send_configoration() function in SimpleServerClass
        }
        else if(response == ProcessResult::RegularMessage){
            ServerEvent server_event = agent->create_agent_event(event);
            m_simple_server_instance.send_to_client(server_event);

            // need to write send_to_client() function in SimpleServerClass
        }
    }
}