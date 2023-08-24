#include "event_from_server.hpp"


namespace dashboard{


ServerEvent::ServerEvent(const QString& a_device_ID, const QString& a_location, 
    const QString& a_type, const QString& a_data, const QDateTime& a_timestamp)
:m_device_ID(a_device_ID) 
,m_location(a_location)
, m_type(a_type)
, m_data(a_data)
, m_timestamp(a_timestamp)
{

}

QString ServerEvent::get_location() const 
{
     return m_location; 
}

QString ServerEvent::get_type() const 
{ 
    return m_type; 
}


QString ServerEvent::get_data() const 
{
    return m_data; 
}

}