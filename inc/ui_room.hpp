#ifndef UI_ROOM_HPP
#define UI_ROOM_HPP

#include <QFrame>
#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>

#include <QApplication>

#include "event.hpp"

namespace spd {
class UIRoom : public QWidget {
    Q_OBJECT
// signals:
//     void button_clicked(size_t const& a_roomn);

public:
    UIRoom(QWidget* parent = nullptr);
    explicit UIRoom(QWidget* parent, size_t const& a_room_num);
    explicit UIRoom(QWidget* parent, Event const &a_event, size_t const& a_room_num);
    ~UIRoom() = default;
    UIRoom(UIRoom const& a_other) = default;

    UIRoom& operator=(UIRoom const& a_other) = default;

    void updata_event(Event const &a_event);
    void change_abnormal(bool const& a_is_abnormal);
    void change_status(QString const& a_status);

private:
    void init_window();
    void init_data(QString const& a_location);
    void init_button();
    void init_data_frame();
    void init_vbox();
    void emit_button_clicked_room();

private:
    QLabel m_room_lab;
    QLabel m_status_lab;
    QLabel m_name_lab;
    QLabel m_pulse_lab;
    QLabel m_bp_lab;
    QLabel m_set_lab;
    QLabel m_temp_lab;

    //QFrame m_data_frame;

    QPushButton *m_details_bt;

    QVBoxLayout *m_vlayout;

private:
    size_t m_room_num;
    bool m_is_abnormal;

};

} // namespace spd

#endif //UI_ROOM_HPP
