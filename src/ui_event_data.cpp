#include "ui_event_data.hpp"

namespace spd {
    
spd::UIEventData::UIEventData(QWidget *parent)
: QColumnView(parent)
{
    init_event("Timestamp: ", "Event Type: ", "Event Data: ");
    this->setMaximumWidth(200);
    this->setMaximumHeight(100);
}

spd::UIEventData::UIEventData(QWidget *parente, QString const &a_timet, QString const &a_type, QString const &a_data)
: QColumnView(parente)
{
    init_event("Timestamp: " + a_timet, "Event Type: " + a_type, "Event Data: " + a_data);
    this->setMaximumWidth(200);
    this->setMaximumHeight(100);
}

spd::UIEventData::~UIEventData()
{
    delete m_time_stamp;
    delete m_type;
    delete m_data;
    delete m_event_data;

}

void UIEventData::change_data(QString const& a_timet, QString const& a_type, QString const& a_data)
{
    m_time_stamp->setText("Timestamp: " + a_timet);
    m_type->setText("Event Type: " + a_type);
    m_data->setText("Event Data: " + a_data);
}

void spd::UIEventData::init_event(QString const &a_timet, QString const &a_type, QString const &a_data)
{

    m_event_data = new QVBoxLayout(this);
    m_time_stamp = new QLabel(a_timet);
    m_type = new QLabel(a_type);
    m_data = new QLabel(a_data);

    m_event_data->addWidget(m_time_stamp);
    m_event_data->addWidget(m_type);
    m_event_data->addWidget(m_data);
}

} // namespace spd
