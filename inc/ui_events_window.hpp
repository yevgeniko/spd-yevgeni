#ifndef UI_EVENT_WINDOW_HPP
#define UI_EVENT_WINDOW_HPP

#include <QWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPushButton>
#include <QList>
#include "event.hpp"
#include "ui_event_data.hpp"

namespace spd {
class UIEventWindow : public QWidget {
    Q_OBJECT
signals:
    void event_screen();

private slots:
    void on_button_click();

public:
    UIEventWindow(QWidget* parent = nullptr);
    ~UIEventWindow();

    void add_event(Event const& a_event);
    void update_event(Event const& a_event, size_t const& a_position);
    void clear_data_list();

private:
    void init_window();

private:
    QVBoxLayout *m_vlayout;
    QHBoxLayout *m_hlayout_bt;
    QPushButton *m_back_bt;

private:
    QList<UIEventData*> m_list_data;

};

} // namespace spd

#endif //UI_EVENT_WINDOW_HPP
