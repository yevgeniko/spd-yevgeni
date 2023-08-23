#include "logger.hpp"

namespace dashboard{


Logger::Logger(const QString& a_file_name)
: m_log_file_name(a_file_name) 
{
}

void Logger::log_event(const QString& a_event_type, const QString& a_event_message) 
{
    QFile file(m_log_file_name + "_Log.txt");
    file.open(QIODevice::WriteOnly | QIODevice::Text);
    QTextStream out(&file);
    out << "[" << QDateTime::currentDateTime().toString() << "] " << a_event_type << ": " << a_event_message << endl;
}

} //namespace dashboard