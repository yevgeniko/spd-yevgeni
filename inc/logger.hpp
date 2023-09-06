#ifndef LOGGER_HPP
#define LOGGER_HPP

#include <QFile>
#include <QTextStream>
#include <QDateTime>
#include "event.hpp"

namespace dashboard {

class Logger
{
public:
    Logger(const QString& a_file_name);

    // Updated to accept an Event object
    void log_event(const Event& event);

private:
    QString m_log_file_name;
};

} // namespace dashboard

#endif // LOGGER_HPP
