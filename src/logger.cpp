#include "logger.hpp"

namespace dashboard {

Logger::Logger(const QString& a_device_name)
: m_log_file_name(a_device_name) 
{
}

void Logger::log_event(const Event& event) 
{
    QFile file(m_log_file_name + "_Log.txt");
    file.open(QIODevice::Append | QIODevice::Text); // Open in append mode
    QTextStream out(&file);
    out << "[" << event.getTimestamp().toString() << "] "
        << "Room: " << event.getEventLocation() 
        << " " << event.getEventType() 
        << ": " << event.getEventData() << endl;
}

} // namespace dashboard
