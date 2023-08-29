#include "ui.hpp"
#include <QTextBrowser>
#include <QDateTime>
#include <memory>
#include <iostream>
#include <QDebug>
#include <QPainter>
#include "const_and_enums.hpp"

namespace spd {

UI::UI()
{
   initwindow();
}

void UI::show_event(QDateTime const& a_timeStamp, QString const& a_eventType, QString const& a_eventData, QString const& a_eventLocation)
{
    QString message = "Received Event in CLIENT:\nTimestamp: "
                         + a_timeStamp.toString("hh:mm:ss") + "\n"
                         + a_eventType + "\n" 
                         + a_eventData + "\n" 
                         + a_eventLocation + "\n";
    m_rooms[0].get()->setText(message);
}

void UI::initwindow()
{
    m_window.setFixedSize(WINDOW_WIDTH, WINDOW_HEIGHT);
    m_window.setWindowTitle(WINDOW_TITLE);
    QPixmap backgroundImage(WIN_BACKGROUND_PATH); // Replace with your image path
        
    QPalette palette;
    backgroundImage = backgroundImage.scaled(m_window.size(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation);  
    palette.setBrush(QPalette::Background, backgroundImage);
    m_window.setAutoFillBackground(true);
    m_window.setPalette(palette);

    m_window.show();
}

} // namespace spd

