#ifndef EVENT_FROM_SERVER_HPP
#define EVENT_FROM_SERVER_HPP

#include <QSettings>
#include <QDateTime>



namespace dashboard {

class ServerEvent {
public:
    ServerEvent(const QString& a_device_ID, const QString& a_location,
        const QString& a_type, const QString& a_data, const QDateTime& a_timestamp);

    QString get_location() const;
    QString get_type() const;
    QString get_data() const; 

private:
    QString m_device_ID;
    QString m_location;
    QString m_type;
    QString m_data;
    QDateTime m_timestamp;
};


} // namespace dashboard

#endif // EVENT_FROM_SERVER_HPP