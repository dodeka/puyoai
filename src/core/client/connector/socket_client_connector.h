#ifndef CORE_CLIENT_CONNECTOR_STDIO_CLIENT_CONNECTOR_H_
#define CORE_CLIENT_CONNECTOR_STDIO_CLIENT_CONNECTOR_H_

#include "core/client/connector/client_connector.h"
#include "net/socket/socket.h"

struct FrameRequest;
struct FrameResponse;

class SocketClientConnector : public ClientConnector {
public:
    explicit SocketClientConnector(net::Socket socket);

    // Returns true if receive suceeded.
    bool receive(FrameRequest* request) override;
    void send(const FrameResponse&) override;

private:
    net::Socket socket_;
};

#endif // CORE_CLIENT_CONNECTOR_STDIO_CLIENT_CONNECTOR_H_
