#include "ui_main_window.hpp"
#include "const_and_enums.hpp"
#include <QPixmap>
#include <QDebug>
#include "const_and_enums.hpp"

namespace spd {
    
spd::UIMainWindow::UIMainWindow(QWidget* parent)
: QWidget(parent)
{
    resize(parent->size());
    init_window();
    init_rooms();
}

void UIMainWindow::init_window()
{
    QPalette palette;
    QPixmap backgroundImage(WIN_BACKGROUND_PATH);
        
    backgroundImage = backgroundImage.scaled(this->size(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation);  
    palette.setBrush(QPalette::Background, backgroundImage);
    setAutoFillBackground(true);
    setPalette(palette);
}

void UIMainWindow::init_rooms()
{
    m_room = new UIRoomBt(this);
    m_room->setText("Room 1");
    m_room->setGeometry(360, 45, 80, 80);
    connect(m_room, SIGNAL(button_clicked()), this, SLOT(on_button_click()));
}

void UIMainWindow::on_button_click()
{
    emit event_screen();
}

} // namespace spd
