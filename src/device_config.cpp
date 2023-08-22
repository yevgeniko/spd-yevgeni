#include "device_config.hpp"

#include <fstream>
#include <stdexcept>

namespace dashboard{



DeviceConfig::DeviceConfig(const std::string& a_config_file) 
{
   read_from_file(a_config_file);
}

void DeviceConfig::read_from_file(const std::string& a_config_file)
{
    std::ifstream file(a_config_file);
    if (!file.is_open()) {
        throw std::runtime_error("Failed to open configuration file");
    }

    DeviceStruct current_device;  
    std::string line;
    while (std::getline(file, line)) {
        size_t delimiter_pos = line.find('=');
        if (delimiter_pos != std::string::npos) {
            std::string key = line.substr(0, delimiter_pos);
            std::string value = line.substr(delimiter_pos + 1);

            if (key == "deviceID") {
                current_device.device_ID = value;
            } else if (key == "type") {
                current_device.type = value;
            } else if (key == "room") {
                current_device.room = value;
            } else if (key == "configuration") {
                current_device.configuration = value;
            }
            m_devices.push_back(current_device);
            current_device = {}; 
        }
    }
}


} //namespace dashboard