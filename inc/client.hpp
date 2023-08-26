#ifndef CLIENT_HPP
#define CLIENT_HPP

#include <QString>
#include <memory>
#include "client_TCP.hpp"

namespace spd {
class Client {
public:
    Client();

    void connect_to_server(const QString &address, quint16 port);

private:
    ClientTCP m_manager;
    //List User; <-id,name,password
};

} // namespace spd

#endif //CLIENT_HPP

