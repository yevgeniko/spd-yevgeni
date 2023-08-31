#ifndef UI_ROOM_BT_HPP
#define UI_ROOM_BT_HPP

#include <QPushButton>
#include <QPainter>
#include <QMouseEvent>

namespace spd {
class UIRoomBt : public QPushButton {
    Q_OBJECT
signals:
    void button_clicked(size_t const& a_roomn);
public:
    UIRoomBt(QWidget *parent = nullptr);
    UIRoomBt(QWidget *parent = nullptr, size_t const& a_roomn = 0);


protected:
    void paintEvent(QPaintEvent* event) override;
    void enterEvent(QEvent* event) override;
    void leaveEvent(QEvent* event) override;
private:
    void emit_button_clicked();
private:
    size_t m_room_num;

};

} // namespace spd

#endif //UI_ROOM_BT_HPP
