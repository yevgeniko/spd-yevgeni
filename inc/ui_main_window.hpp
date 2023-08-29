#ifndef UI_MAIN_WINDOW_HPP
#define UI_MAIN_WINDOW_HPP

#include <QWidget>
#include <QMainWindow>
#include <QSharedPointer>
#include <QPixmap>

namespace spd {
class UIMainWindow : public QWidget {
public:
    UIMainWindow(QMainWindow & a_main_win);
    ~UIMainWindow()= default;

    UIMainWindow(UIMainWindow const& a_other) = default;
    UIMainWindow& operator=(UIMainWindow const& a_other)= default;

    void resizeEvent(QMainWindow & a_main_win);
private:
   QWidget* initwindow(QMainWindow & a_main_win);
private:
    QWidget* m_window;
    QPixmap backgroundImage;
};
    
} // namespace spd

#endif //UI_MAIN_WINDOW_HPP
