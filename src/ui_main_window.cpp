#include "ui_main_window.hpp"
#include "const_and_enums.hpp"
#include <QPixmap>
#include "const_and_enums.hpp"

namespace spd {
    
spd::UIMainWindow::UIMainWindow(QMainWindow &a_main_win)
: m_window{initwindow(a_main_win)}
{
}

void UIMainWindow::resizeEvent(QMainWindow &a_main_win)
{
    backgroundImage = backgroundImage.scaled(a_main_win.size(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation);  
    QPalette palette;
    palette.setBrush(QPalette::Background, backgroundImage);
    setAutoFillBackground(true);
    setPalette(palette);
}

QWidget *UIMainWindow::initwindow(QMainWindow &a_main_win)
{
    QWidget* mainwindow (new QWidget(&a_main_win));
    mainwindow->resize(WINDOW_WIDTH, WINDOW_HEIGHT);
    QPixmap backgroundImage(WIN_BACKGROUND_PATH); // Replace with your image path
        
    QPalette palette;
    backgroundImage = backgroundImage.scaled(mainwindow->size(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation);  
    palette.setBrush(QPalette::Background, backgroundImage);
    mainwindow->setAutoFillBackground(true);
    mainwindow->setPalette(palette);
    return mainwindow;
}

} // namespace spd
