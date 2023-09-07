#include "ui_events_window.hpp"
#include <QMainWindow>
#include <QDebug>
#include "const_and_enums.hpp"
#include "ui_event_data.hpp"

namespace spd {
UIEventWindow::UIEventWindow(QWidget* parent)
: QWidget(parent)
, m_vlayout{new QVBoxLayout(this)}
, m_hlayout_bt{new QHBoxLayout(this)}
, m_back_bt{new QPushButton("Back", this)}
, m_location{new QLabel(this)}
, m_id{new QLabel(this)}
, m_name{new QLabel(this)}
, m_is_empty{true}
{
    init_window();
}

UIEventWindow::~UIEventWindow()
{
    for(auto & data: m_list_data) {
        delete data;
    }

    delete m_location;
    delete m_id;
    delete m_name;

    delete m_back_bt;
    delete m_hlayout_bt;
    delete m_vlayout;
}

void UIEventWindow::add_event(Event const &a_event)
{ 
    m_location->setText("Room " + a_event.getEventLocation());
    m_id->setText("ID: 569305");
    m_name->setText("Name: patient");
    m_list_data.append(new UIEventData(this
                        , a_event.getTimestamp().toString("hh:mm:ss")
                        , a_event.getEventType()
                        , a_event.getEventData()));
    for(auto &data: m_list_data) {
        m_vlayout->addWidget(data, 0, Qt::AlignLeft);
    }
}

void UIEventWindow::update_event(Event const &a_event, size_t const &a_position)
{
    m_location->setText("Room " + a_event.getEventLocation());
    m_id->setText("ID: 569305");
    m_name->setText("Name: patient");
    m_list_data[a_position]->change_data(a_event.getTimestamp().toString("hh:mm:ss") 
                        , a_event.getEventType()
                        , a_event.getEventData());
}

void UIEventWindow::clear_data_list()
{

}

void UIEventWindow::init_window()
{
    m_back_bt->setMaximumWidth(50);
    m_back_bt->setMaximumHeight(30);
    m_hlayout_bt->addWidget(m_back_bt ,0 , Qt::AlignLeft);

    m_location->setText("Room x");
    m_id->setText("ID: 569305");
    m_name->setText("Name: patient");

    m_hlayout_bt->addWidget(m_location,0 , Qt::AlignLeft);
    m_hlayout_bt->addWidget(m_id,0 , Qt::AlignLeft);
    m_hlayout_bt->addWidget(m_name,0 , Qt::AlignLeft);

    m_vlayout->addLayout(m_hlayout_bt);

    connect(m_back_bt, &QPushButton::clicked, [this]() {
        emit on_button_click();
    });
    for(size_t index = 0; index < 4; ++index) {
        m_list_data.append(new UIEventData(this));
    }
    for(auto& event: m_list_data) {
        m_vlayout->addWidget(event, 0, Qt::AlignTop);
    }
}

void UIEventWindow::on_button_click()
{
    emit event_screen();
}

} // namespace spd
