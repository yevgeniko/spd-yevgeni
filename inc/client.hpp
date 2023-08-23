#ifndef CLIENT_HPP
#define CLIENT_HPP

#include <QString>
#include <memory>
#include "client_manager.hpp"

namespace spd {
class Client {
public:
    Client();

    void connect_to_server(const QString &address, quint16 port);

private:
    ClientManager m_manager;
    //List User; <-id,name,password
};

} // namespace spd

#endif //CLIENT_HPP

