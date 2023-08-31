#include "ui_room_bt.hpp"

namespace spd {

spd::UIRoomBt::UIRoomBt(QWidget *parent)
: QPushButton(parent) 
{
    setAttribute(Qt::WA_TranslucentBackground);
    connect(this, &QPushButton::clicked, this, &UIRoomBt::emit_button_clicked);
}

UIRoomBt::UIRoomBt(QWidget *parent, size_t const &a_roomn)
: QPushButton(parent)
, m_room_num(a_roomn)
{
    setAttribute(Qt::WA_TranslucentBackground);
    connect(this, &QPushButton::clicked, this, &UIRoomBt::emit_button_clicked);
}

void spd::UIRoomBt::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    QColor bgColor = palette().color(QPalette::Button);
    bgColor.setAlpha(100);

    painter.fillRect(rect(), bgColor);

    QPushButton::paintEvent(event);
}

void spd::UIRoomBt::enterEvent(QEvent *event)
{
    setCursor(Qt::PointingHandCursor);
    QPushButton::enterEvent(event);
}

void spd::UIRoomBt::leaveEvent(QEvent *event)
{
    unsetCursor();
    QPushButton::leaveEvent(event);
}

void spd::UIRoomBt::emit_button_clicked()
{    
    emit button_clicked(m_room_num);   
}

} // namespace spd
