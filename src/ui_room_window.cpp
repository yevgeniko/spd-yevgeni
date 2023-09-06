#include "ui_room_window.hpp"
#include "const_and_enums.hpp"
#include "ui_room.hpp"

namespace spd {

UIRoomWindow::UIRoomWindow(QWidget* parent)
: QWidget(parent)
, m_frame{new QFrame(this)}
, m_room_layout{new QHBoxLayout(this)}
, m_scroll_bar{new QScrollBar(Qt::Horizontal ,this)}
{
    init_window();
    init_frame();
    init_layout();

    init_rooms();
}

UIRoomWindow::~UIRoomWindow()
{
    
    delete m_scroll_bar;
    delete m_room_layout;
    delete m_frame;
}

void UIRoomWindow::add_room(Event const &a_event)
{
    UIRoom* room = new UIRoom(this, a_event, m_rooms.size());
    m_rooms.push_back(room);
    m_room_layout->addWidget(room);
    //connect(m_rooms[m_rooms.size() - 1], &UIRoom::button_clicked, this, &UIRoomWindow::on_button_click);
}

void UIRoomWindow::update_room(Event const &a_event, size_t const &a_position)
{
    m_rooms[a_position]->updata_event(a_event);
}

void UIRoomWindow::init_window()
{
    this->setWindowTitle(WINDOW_TITLE);
}

void UIRoomWindow::init_frame()
{
    m_frame->setGeometry(100, 20, 1000, 300);
    m_frame->setFrameShape(QFrame::WinPanel);
    m_frame->setFrameShadow(QFrame::Raised);
    m_frame->setLineWidth(1);
}

void UIRoomWindow::init_layout()
{
    m_room_layout->addWidget(m_scroll_bar);
}

void UIRoomWindow::init_rooms()
{
    for(size_t i = 0; i < 4; ++i) {
        m_rooms.push_back(new UIRoom(this, i + 1));
    }
}

// void UIRoomWindow::on_button_click(size_t const& a_roomn)
// {
//     //emit event_screen_main(a_roomn);
// }

} // namespace spd
