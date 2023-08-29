#ifndef UI_HPP
#define UI_HPP

#include <qmainwindow.h>
#include <memory>
#include <QPushButton>
#include <QDateTime>
#include <QList>
#include <QDebug>
#include "ui_main_window.hpp"

namespace spd {
    
class UI : public QMainWindow {

Q_OBJECT

public:
    UI();

    void show_event(QDateTime const& a_timeStamp, QString const& a_eventType, QString const& a_eventData, QString const& a_eventLocation);
    void resizeEvent(QResizeEvent *event) override;

private:
    void init_window();
    void init_room();


private:
    QMainWindow m_window;
    UIMainWindow m_main_window;
    QList<QPushButton*> m_rooms;
};
    
} // namespace spd

#endif //UI_HPP