#include "ui_room.hpp"
#include "const_and_enums.hpp"

#include <QPainter>

namespace spd {
UIRoom::UIRoom(QWidget *parent)
: QWidget(parent)
, m_vlayout{new QVBoxLayout(this)}
, m_details_bt{new QPushButton(this)}
{
}

UIRoom::UIRoom(QWidget *parent, size_t const &a_room_num)
: QWidget(parent)
, m_is_abnormal{false}
, m_room_num{a_room_num}
{
    init_window();
    init_data_frame();
    init_data(QString::number(static_cast<qulonglong>(a_room_num)));
    init_button();
    init_vbox();
}

spd::UIRoom::UIRoom(QWidget* parent, Event const &a_event, size_t const& a_room_num)
: QWidget(parent)
, m_is_abnormal{false}
, m_room_num{a_room_num}
{
    init_window();
    init_data_frame();
    init_data(a_event.getEventLocation());
    init_button();
    init_vbox();
    updata_event(a_event);
}

void UIRoom::updata_event(Event const &a_event)
{
    if(a_event.getEventType() == PULSE) {
        m_pulse_lab.setText(PULSE + ": " + a_event.getEventData());
    } else if(a_event.getEventType() == BP) {
        m_bp_lab.setText(BP + ": " + a_event.getEventData());
    } else if(a_event.getEventType() == SET) {
        m_set_lab.setText(SET + ": " + a_event.getEventData());
    } else if(a_event.getEventType() == TEMP) {
        m_temp_lab.setText(TEMP + ": " + a_event.getEventData());
    }
}

void UIRoom::init_window()
{
    this->resize(250, 300);
    this->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
}

void UIRoom::init_data(QString const& a_location)
{
    m_room_lab.setText("Room " + a_location);

    m_status_lab.setText(PATIENT_STATUS);
    m_status_lab.setStyleSheet("background-color: yellow;");
    // QPainter painter(&m_status_lab);
    // painter.fillRect(rect(), QColor(0, 255, 0));

    m_name_lab.setText("Name: Noam Sharon");

    m_pulse_lab.setParent(this);
    m_pulse_lab.setText(PULSE);

    m_bp_lab.setParent(this);
    m_bp_lab.setText(BP);

    m_set_lab.setParent(this);
    m_set_lab.setText(SET);

    m_temp_lab.setParent(this);
    m_temp_lab.setText(TEMP);

}

void UIRoom::init_button()
{
    m_details_bt->resize(70,30);
    m_details_bt->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    m_details_bt->setText(DETAILS);
    // connect(&m_details_bt, &QPushButton::clicked, [this]() {
    //     emit emit_button_clicked();
    // });
}

void UIRoom::init_data_frame()
{
    // m_data_frame.setParent(this);
    // m_data_frame.resize(200, 100);
    // m_data_frame.setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
}

void UIRoom::init_vbox()
{
    m_vlayout->setParent(this);
    m_vlayout->addWidget(&m_room_lab);
    m_vlayout->addWidget(&m_status_lab);
    m_vlayout->addWidget(&m_name_lab);
    m_vlayout->addWidget(&m_pulse_lab);
    m_vlayout->addWidget(&m_bp_lab);
    m_vlayout->addWidget(&m_set_lab);
    m_vlayout->addWidget(&m_temp_lab);
    m_vlayout->addWidget(m_details_bt);
}

// void UIRoom::emit_button_clicked_room()
// {
//     emit button_clicked(m_room_num);
// }

} // namespace spd
