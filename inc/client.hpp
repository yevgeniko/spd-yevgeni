#ifndef CLIENT_HPP
#define CLIENT_HPP

#include <QString>
#include <memory>
#include "client_manager.hpp"

namespace spd {
class Client {
public:
    explicit Client(QString const& aa_id, QString const& a_firstn, QString const& a_lastn, QList<QString> a_rooms);

private:
    QString m_id;
    QString m_first_name;
    QString m_last_name;
    QList<Event> m_rooms;
};

} // namespace spd

#endif //CLIENT_HPP

