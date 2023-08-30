#ifndef UI_MAIN_WINDOW_HPP
#define UI_MAIN_WINDOW_HPP

#include <QWidget>
#include <QMainWindow>
#include <QSharedPointer>
#include <QPixmap>
#include "ui_room_bt.hpp"

namespace spd {
class UIMainWindow : public QWidget {
    Q_OBJECT
signals:
    void event_screen();
private slots:
    void on_button_click();

public:
    UIMainWindow(QWidget* parent = nullptr);
private:
   void init_window();
   void init_rooms();
private:
    UIRoomBt *m_room;
};
    
} // namespace spd

#endif //UI_MAIN_WINDOW_HPP
