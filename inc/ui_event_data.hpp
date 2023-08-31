#ifndef UI_EVENT_DATA_HPP
#define UI_EVENT_DATA_HPP

#include <QWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QString>
#include <QColumnView>

namespace spd {
class UIEventData : public QColumnView {
public:
    UIEventData(QWidget* parent = nullptr);
    UIEventData(QWidget* parent, QString const& a_id, QString const& a_name, QString const& a_timet, QString const& a_type, QString const& a_data, QString const& a_location);
    ~UIEventData();

    void change_data(QString const& a_id, QString const& a_name, QString const& a_timet, QString const& a_type, QString const& a_data, QString const& a_location);
    
private:
    void init_event(QString const& a_id, QString const& a_name, QString const& a_timet, QString const& a_type, QString const& a_data, QString const& a_location);
private:
    QHBoxLayout *m_vlayout;

    QVBoxLayout *m_patient_data;
    QLabel * m_id;
    QLabel * m_name;

    QVBoxLayout *m_event_data;
    QLabel * m_time_stamp;
    QLabel * m_type;
    QLabel * m_data;
    QLabel * m_location;
};
} // namespace spd

#endif //UI_EVENT_DATA_HPP
