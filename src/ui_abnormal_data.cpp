#include "ui_abnormal_data.hpp"

namespace spd {

UIAbnorlamData::UIAbnorlamData(QWidget *parent)
{
    init_event("Room ", "Timestamp: ", "Event Type: ", "Event Data: ");
    this->setMaximumWidth(200);
    this->setMaximumHeight(100);
    this->setStyleSheet("background-color: red;");
}

UIAbnorlamData::UIAbnorlamData(QWidget *parent, QString const &a_location, QString const &a_timet, QString const &a_type, QString const &a_data)
{
    init_event("Room:" + a_location ,"Timestamp: " + a_timet, "Event Type: " + a_type, "Event Data: " + a_data);
    this->setMaximumWidth(200);
    this->setMaximumHeight(100);
    this->setStyleSheet("background-color: red;");
}

UIAbnorlamData::~UIAbnorlamData()
{
    delete m_time_stamp;
    delete m_type;
    delete m_data;
    delete m_event_data;
    delete m_location;
}

void UIAbnorlamData::change_data(QString const &a_location, QString const &a_timet, QString const &a_type, QString const &a_data)
{
    m_location->setText("Room " + a_location);
    m_time_stamp->setText("Timestamp: " + a_timet);
    m_type->setText("Event Type: " + a_type);
    m_data->setText("Event Data: " + a_data);
}

void UIAbnorlamData::init_event(QString const &a_location, QString const &a_timet, QString const &a_type, QString const &a_data)
{
    m_event_data = new QVBoxLayout(this);
    m_time_stamp = new QLabel(a_timet);
    m_type = new QLabel(a_type);
    m_data = new QLabel(a_data);
    m_location = new QLabel(a_location);

    m_event_data->addWidget(m_location);
    m_event_data->addWidget(m_time_stamp);
    m_event_data->addWidget(m_type);
    m_event_data->addWidget(m_data);
}

} // namespace spd
