#include "event_handler_base.hpp"

EventHandlerBase::EventHandlerBase(qint16 lower_limit, qint16 higher_limit)
    : m_lower_limit(lower_limit), m_higher_limit(higher_limit)
    {}

EventHandlerBase::~EventHandlerBase() = default;