#ifndef UI_MAIN_WINDOW_HPP
#define UI_MAIN_WINDOW_HPP

#include <QWidget>
#include <QMainWindow>
#include <QSharedPointer>
#include <QPixmap>
#include <QList>
#include "ui_room_bt.hpp"

namespace spd {
class UIMainWindow : public QWidget {
    Q_OBJECT
signals:
    void event_screen_main(size_t const& a_roomn);
private slots:
    void on_button_click(size_t const& a_roomn);

public:
    UIMainWindow(QWidget* parent = nullptr);
    ~UIMainWindow();

    void abnormal_event(size_t const& a_room_num);

private:
   void init_window();
   void init_rooms();
private:
    QList<UIRoomBt*> m_rooms;
    bool m_is_abnormal;
};
    
} // namespace spd

#endif //UI_MAIN_WINDOW_HPP
