#ifndef UI_ABNORMAL_DATA_HPP
#define UI_ABNORMAL_DATA_HPP

#include <QWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QString>
#include <QColumnView>

namespace spd {
class UIAbnorlamData : public QColumnView {
public:
    UIAbnorlamData(QWidget* parent = nullptr);
    UIAbnorlamData(QWidget* parent, QString const& a_location, QString const& a_timet, QString const& a_type, QString const& a_data);
    ~UIAbnorlamData();

    void change_data(QString const& a_location, QString const& a_timet,  QString const& a_type, QString const& a_data);
    
private:
    void init_event(QString const& a_location, QString const& a_timet, QString const& a_type, QString const& a_data);

private:
    QVBoxLayout *m_event_data;
    QLabel * m_location;
    QLabel * m_time_stamp;
    QLabel * m_type;
    QLabel * m_data;
};
} // namespace spd

#endif //UI_ABNORMAL_DATA_HPP
