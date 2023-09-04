#ifndef EVENT_HANDLER_BASE_HPP
#define EVENT_HANDLER_BASE_HPP

#include <QObject>
#include "event.hpp"
#include "logger.hpp"

class EventHandlerBase : public QObject
{
    Q_OBJECT
public:
    EventHandlerBase(qint16 lower_limit, qint16 higher_limit);
    virtual ~EventHandlerBase();

    virtual void handleEvent(Event& event) = 0;

protected:
    qint16 m_lower_limit;
    qint16 m_higher_limit;
};

#endif // EVENT_HANDLER_BASE_HPP
