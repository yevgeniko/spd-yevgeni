#ifndef AI_HPP
#define AI_HPP

#include <cstdlib>
#include <QObject>
#include "event.hpp"
#include <QMap>

// Undefine slots (used by Qt)
#undef slots
#include <Python.h>
#define slots Q_SLOTS

class AI : public QObject
{
    Q_OBJECT

public:
    AI();
    ~AI();
    int connect_to_tree(const double& a_saturation, const double& a_temp, const double& a_pulse);
    void buffer_event(const Event& event);

signals:
    void predictionReady(int prediction, int room);

private:
    QMap<int,QMap<QString, QString>> m_package; // room number (type, data) 
};

#endif //AI_HPP
