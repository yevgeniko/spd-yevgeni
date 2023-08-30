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
{
    init_window();
}

UIEventWindow::~UIEventWindow()
{
    for(auto & data: m_list_data) {
        delete data;
    }
    delete m_hlayout_bt;
    delete m_back_bt;
    delete m_vlayout;
}

void UIEventWindow::add_event(Event const &a_event)
{
    m_list_data.append(new UIEventData(this, "123", "name"
                        , a_event.getTimestamp().toString("hh:mm:ss")
                        , a_event.getEventType()
                        , a_event.getEventData()
                        , a_event.getEventLocation()));
    for(auto &data: m_list_data) {
        m_vlayout->addWidget(data);
    }
}

void UIEventWindow::init_window()
{
    m_back_bt->resize(30,30);
    m_hlayout_bt->addWidget(m_back_bt);
    m_vlayout->addLayout(m_hlayout_bt);
    connect(m_back_bt, &QPushButton::clicked, [this]() {
        emit on_button_click();
    });
    
}

void UIEventWindow::on_button_click()
{
    emit event_screen();
}

} // namespace spd
