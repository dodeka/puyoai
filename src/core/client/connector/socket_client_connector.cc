#include "core/client/connector/socket_client_connector.h"

SocketClientConnector::SocketClientConnector(net::Socket socket) :
    socket_(std::move(socket))
{
}
