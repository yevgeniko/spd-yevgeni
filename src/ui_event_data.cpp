#include "ui_event_data.hpp"

namespace spd {
    
spd::UIEventData::UIEventData(QWidget *parent)
: QColumnView(parent)
{
    init_event("ID: ", "Name: ", "Timestamp: ", "Event Type: ", "Event Data: ", "Event Location: ");
}

spd::UIEventData::UIEventData(QWidget *parent, QString const &a_id, QString const &a_name, QString const &a_timet, QString const &a_type, QString const &a_data, QString const &a_location)
: QColumnView(parent)
{
    init_event("ID: " + a_id, "Name: " + a_name, "Timestamp: " + a_timet, "Event Type: " + a_type, "Event Data: " + a_data, "Event Location: " + a_location);
}

spd::UIEventData::~UIEventData()
{
    delete m_id;
    delete m_name;
    delete m_patient_data;

    delete m_time_stamp;
    delete m_type;
    delete m_data;
    delete m_location;
    delete m_event_data;

    delete m_vlayout;
}

void UIEventData::change_data(QString const &a_data)
{
    m_data->setText(a_data);
}

void spd::UIEventData::init_event(QString const &a_id, QString const &a_name, QString const &a_timet, QString const &a_type, QString const &a_data, QString const &a_location)
{
    m_vlayout = new QHBoxLayout(this);
    m_patient_data = new QVBoxLayout(this);
    m_vlayout->addLayout(m_patient_data);
    m_id = new QLabel(a_id);
    m_name = new QLabel(a_name);

    m_patient_data->addWidget(m_id);
    m_patient_data->addWidget(m_name);

    m_event_data = new QVBoxLayout(this);
    m_vlayout->addLayout(m_event_data);
    m_time_stamp = new QLabel(a_timet);
    m_type = new QLabel(a_type);
    m_data = new QLabel(a_data);
    m_location = new QLabel(a_location);

    m_event_data->addWidget(m_time_stamp);
    m_event_data->addWidget(m_type);
    m_event_data->addWidget(m_data);
    m_event_data->addWidget(m_location);
}

} // namespace spd
