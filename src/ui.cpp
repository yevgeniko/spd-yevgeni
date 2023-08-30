#include "ui.hpp"
#include <QTextBrowser>
#include <QDateTime>
#include <memory>
#include <iostream>
#include <QDebug>
#include <QPainter>
#include <QResizeEvent>
#include <QVBoxLayout>

#include "const_and_enums.hpp"
#include "ui_main_window.hpp"
#include "ui_room_bt.hpp"
#include "ui_events_window.hpp"

namespace spd {


UI::UI(QWidget* parent)
: QWidget(parent)
{
    init_window();
    init_screens();
    this->show();
}

UI::~UI()
{
    for(auto & room: m_rooms) {
        delete room;
    }
    delete m_main_window;
    delete m_event_window;
    delete m_stacked_widget;
}

void UI::show_event(QDateTime const& a_timeStamp, QString const& a_eventType, QString const& a_eventData, QString const& a_eventLocation)
{
    QString message = "Received Event in CLIENT:\nTimestamp: "
                         + a_timeStamp.toString("hh:mm:ss") + "\n"
                         + a_eventType + "\n" 
                         + a_eventData + "\n" 
                         + a_eventLocation + "\n";
    m_rooms[0]->setText(message);
}

void UI::add_event(Event const &a_event)
{
    m_event_window->add_event(a_event);
}

void UI::switch_to_main_screen() 
{
    m_stacked_widget->setCurrentIndex(0);
}

void UI::switch_to_event_screen()
{
    m_stacked_widget->setCurrentIndex(1);
}

void UI::init_screens()
{
    m_stacked_widget = new QStackedWidget(this);
    setLayout(new QVBoxLayout());
    this->layout()->addWidget(m_stacked_widget);

    m_main_window = new UIMainWindow(this);
    m_event_window = new UIEventWindow(this);

    m_stacked_widget->addWidget(m_main_window);
    m_stacked_widget->addWidget(m_event_window);

    connect(m_main_window, SIGNAL(event_screen()), this, SLOT(switch_to_event_screen()));
    connect(m_event_window, SIGNAL(event_screen()), this, SLOT(switch_to_main_screen()));

    m_stacked_widget->setCurrentWidget(m_main_window);
}

void UI::init_window()
{
    setFixedSize(WINDOW_WIDTH, WINDOW_HEIGHT);
    setWindowTitle(WINDOW_TITLE);
}

void UI::init_room()
{
    m_rooms.append(new UIRoomBt(this));
    m_rooms[0]->setText("Room 1");
    m_rooms[0]->setGeometry(360, 45, 80, 80);
}

} // namespace spd

