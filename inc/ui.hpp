#ifndef UI_HPP
#define UI_HPP

#include <qmainwindow.h>
#include <memory>
#include <QTextBrowser>
#include <QDateTime>
#include <QList>

namespace spd {
    
class UI : public QMainWindow {

Q_OBJECT

public:
    UI();

    void show_event(QDateTime const& a_timeStamp, QString const& a_eventType, QString const& a_eventData, QString const& a_eventLocation);
private:
    void initwindow();

private:
    QMainWindow m_window;
    QList<QScopedPointer<QTextBrowser>> m_rooms;
};
    
} // namespace spd

#endif //UI_HPP