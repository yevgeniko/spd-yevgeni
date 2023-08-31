#ifndef LOGGER_HPP
#define LOGGER_HPP


#include <QFile>
#include <QTextStream>
#include <QDateTime>


// namespace dashboard{

class Logger {
public:

    Logger(const QString& a_file_name);

    void log_event(const QString& a_event_type, const QString& a_event_message,
    const QString& a_event_room);

private:
    QString m_log_file_name;
};

// } // namespace dashboard


#endif // LOGGER_HPP