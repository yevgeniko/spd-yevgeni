#ifndef UI_HPP
#define UI_HPP

#include <qmainwindow.h>
#include <QPushButton>
#include <QDateTime>
#include <QList>
#include <QDebug>
#include <QStackedWidget>
#include <QWidget>
#include "ui_main_window.hpp"
#include "ui_events_window.hpp"
#include "event.hpp"

namespace spd {
    
class UI : public QWidget {

    Q_OBJECT
signals:
    void set_room_num(int a_rnum);

private slots:
    void switch_to_main_screen();
    void switch_to_event_screen();

public:
    UI(QWidget* parent = nullptr);
    ~UI();

    void show_event(QDateTime const& a_timeStamp, QString const& a_eventType, QString const& a_eventData, QString const& a_eventLocation);
    void add_event(Event const& a_event);

private:
    void init_screens();
    void init_window();
    void init_room();


private:
    QStackedWidget* m_stacked_widget;
    UIMainWindow* m_main_window;
    UIEventWindow* m_event_window;
    QList<QPushButton*> m_rooms;
};
    
} // namespace spd

#endif //UI_HPP