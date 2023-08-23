#include "server.hpp"
#include <iostream>

#include <QCoreApplication>
#include <QDebug>


int main() {
    try {
        dashboard::Server server;

        for (const auto& devicePtr : server.server_devices()) {
            std::cout << "Device ID: " << devicePtr->getDeviceID().toStdString() << std::endl;
            std::cout << "Device Type: " << devicePtr->getType().toStdString() << std::endl;
            std::cout << "Device Room: " << devicePtr->getRoom().toStdString() << std::endl;
            std::cout << "Device Configuration: " << devicePtr->getConfiguration().toStdString() << std::endl;
            std::cout << "----------------------------" << std::endl;
        }
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
    return 0;
}