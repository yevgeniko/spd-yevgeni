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
    delete m_main_window;
    delete m_event_window;
    delete m_stacked_widget;
}



void UI::add_event(Event const &a_event)
{
    m_event_window->add_event(a_event);
}

void UI::switch_to_main_screen() 
{
    emit set_room_num(0);
    m_stacked_widget->setCurrentIndex(0);
}

void UI::switch_to_event_screen(size_t const& a_roomn)
{
    emit set_room_num(a_roomn);
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

    connect(m_main_window, &UIMainWindow::event_screen_main, this,  &UI::switch_to_event_screen);
    connect(m_event_window, &UIEventWindow::event_screen, this, &UI::switch_to_main_screen);

    m_stacked_widget->setCurrentWidget(m_main_window);
}

void UI::init_window()
{
    setFixedSize(WINDOW_WIDTH, WINDOW_HEIGHT);
    setWindowTitle(WINDOW_TITLE);
}

} // namespace spd

