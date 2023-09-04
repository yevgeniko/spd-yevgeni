#include <QDebug>
#include <QStringList>
#include "pulse_event_handler.hpp"

PulseEventHandler::PulseEventHandler(qint16 lower_limit, qint16 higher_limit)
    : EventHandlerBase(lower_limit, higher_limit) {}

void PulseEventHandler::handleEvent(const Event& event)
{
    if (event.getEventData().toInt() < m_lower_limit || 
        event.getEventData().toInt() > m_higher_limit) 
    {
        const_cast<Event&>(event).set_abnormal("ABNORMAL PULSE");
        emit alertGenerated(event);  // Emit the alert signal
    }

    int room_number = event.getEventLocation().toInt();
    emit eventProcessed(room_number, event); // Emit the processed event signal
}


BloodPressureEventHandler::BloodPressureEventHandler(qint16 lower_limit_systolic, qint16 higher_limit_systolic,
                                                     qint16 lower_limit_diastolic, qint16 higher_limit_diastolic)
    : EventHandlerBase(lower_limit_systolic, higher_limit_systolic),
      m_lower_limit_diastolic(lower_limit_diastolic), m_higher_limit_diastolic(higher_limit_diastolic) {}

void BloodPressureEventHandler::handleEvent(const Event& event)
{
    qDebug() << "IN Blood Pressure Event Handler with data:" << event.getEventData();
    int room_number = event.getEventLocation().toInt();

    QStringList pressures = event.getEventData().split("/");
    int systolic = pressures[0].toInt();
    int diastolic = pressures[1].toInt();

    if (systolic < m_lower_limit || systolic > m_higher_limit || diastolic < m_lower_limit_diastolic || diastolic > m_higher_limit_diastolic) {
        const_cast<Event&>(event).set_abnormal("ABNORMAL BP");
        emit alertGenerated(event);  // Emit the alert signal
    }

    emit eventProcessed(room_number, event); // Emit the processed event signal
}

SaturationEventHandler::SaturationEventHandler(qint16 lower_limit, qint16 higher_limit)
    : EventHandlerBase(lower_limit, higher_limit) {}

void SaturationEventHandler::handleEvent(const Event& event)
{
    qDebug() << "IN Saturation Event Handler with data:" << event.getEventData();
    int room_number = event.getEventLocation().toInt();

    if (event.getEventData().toInt() < m_lower_limit || event.getEventData().toInt() > m_higher_limit) {
        const_cast<Event&>(event).set_abnormal("ABNORMAL SAT");
        emit alertGenerated(event);  // Emit the alert signal
    }

    emit eventProcessed(room_number, event); // Emit the processed event signal
}

TemperatureEventHandler::TemperatureEventHandler(qint16 lower_limit, qint16 higher_limit)
    : EventHandlerBase(lower_limit, higher_limit) {}

void TemperatureEventHandler::handleEvent(const Event& event)
{
    qDebug() << "IN Temperature Event Handler with data:" << event.getEventData();
    int room_number = event.getEventLocation().toInt();

    if (event.getEventData().toDouble() < m_lower_limit || event.getEventData().toDouble() > m_higher_limit) {
        const_cast<Event&>(event).set_abnormal("ABNORMAL TEMP");
        emit alertGenerated(event);  // Emit the alert signal
    }

    emit eventProcessed(room_number, event); // Emit the processed event signal
}