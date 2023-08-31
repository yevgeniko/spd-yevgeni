#include "logger.hpp"

// namespace dashboard{


Logger::Logger(const QString& a_device_name)
: m_log_file_name(a_device_name) 
{
}

void Logger::log_event(const QString& a_event_type, const QString& a_event_message, const QString& a_event_room) 
{
    QFile file(m_log_file_name + "_Log.txt");
    file.open(QIODevice::Append | QIODevice::Text); // Open in append mode
    QTextStream out(&file);
    out << "[" << QDateTime::currentDateTime().toString() << "] "<< "Room: " 
    << a_event_room<< "  " << a_event_type << ": " << a_event_message << endl;
}


// } //namespace dashboard