#include "ui_main_window.hpp"
#include "const_and_enums.hpp"
#include <QPixmap>
#include <QDebug>
#include <QString>
#include "const_and_enums.hpp"

namespace spd {
    
spd::UIMainWindow::UIMainWindow(QWidget* parent)
: QWidget(parent)
{
    resize(parent->size());
    init_window();
    init_rooms();
}

UIMainWindow::~UIMainWindow()
{
    for(auto &room: m_rooms) {
        delete room;
    }
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
    int distance = 100;
    for(size_t index = 0; index < NUM_OF_ROOMS; ++index) {
        m_rooms[index] = new UIRoomBt(this, index + 1);
        m_rooms[index]->setText(("room " + QString::number(index + 1)));
        m_rooms[index]->setGeometry(360 + (index*distance), 45, 80, 80);
        connect(m_rooms[index], &UIRoomBt::button_clicked, this, &UIMainWindow::on_button_click);
        if(index == 1) {
            distance = 105;
        }
    }
}

void UIMainWindow::on_button_click(size_t const& a_roomn)
{
    emit event_screen_main(a_roomn);
}

} // namespace spd
