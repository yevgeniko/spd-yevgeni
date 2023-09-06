#ifndef UI_ROOM_WINDOW_HPP
#define UI_ROOM_WINDOW_HPP

#include <QWidget>
#include <QHBoxLayout>
#include <QScrollBar>
#include <QFrame>
#include <QString>

#include "ui_room.hpp"
#include "event.hpp"

namespace spd {
class UIRoomWindow : public QWidget {
    Q_OBJECT
// signals:
//     void event_screen_main(size_t const& a_roomn);
// private slots:
//     void on_button_click(size_t const& a_roomn);

public:
    UIRoomWindow(QWidget* parent = nullptr);
    ~UIRoomWindow();

    void add_room(Event const& a_event);
    void update_room(Event const& a_event, size_t const& a_position);

    void set_abnormal(Event const& a_event);
    void patient_status(QString const& a_status, size_t const& a_room_num);

    void details_of_event(Event const& a_event, QString const& a_max, QString const& a_min);
    void show_details(bool const& a_is_details);
private:
    void init_window();
    void init_frame();
    void init_layout();
    void init_rooms();

private:
    QFrame *m_frame;
    QHBoxLayout *m_room_layout;
    QScrollBar *m_scroll_bar;

private:
    QList<UIRoom*> m_rooms;
    bool m_show_details;


};

} // namespace spd

#endif //UI_ROOM_WINDOW_HPP