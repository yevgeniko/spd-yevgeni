#include "agent_manager.hpp"
#include <iostream>

#include <QCoreApplication>
#include <QDebug>


int main() {
    try {
        dashboard::AgentManager Agent_Manager;

        for (const auto& devicePtr : Agent_Manager.server_devices()) {
            std::cout << "Device ID: " << devicePtr->getDeviceID().toStdString() << std::endl;
            std::cout << "Device Type: " << devicePtr->getType().toStdString() << std::endl;
            std::cout << "Device Room: " << devicePtr->getRoom().toStdString() << std::endl;
            std::cout << "Device Configuration: " << devicePtr->getConfiguration().toStdString() << std::endl;
            std::cout << "----------------------------" << std::endl;
            devicePtr->log_unNormal("Device Type: ", "Device Configuration: ");
        }
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
    return 0;
}