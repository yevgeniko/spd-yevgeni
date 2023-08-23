#ifndef LOGGER_HPP
#define LOGGER_HPP


#include <QFile>
#include <QTextStream>
#include <QDateTime>

#include "device_config.hpp"

namespace dashboard{

class Logger {
public:

    Logger(const QString& a_file_name);

    void log_event(const QString& a_even_type, const QString& a_event_message);

private:
    QString m_log_file_name;
};

} // namespace dashboard


#endif // LOGGER_HPP