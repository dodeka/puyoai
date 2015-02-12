#ifndef CORE_SERVER_CONNECTOR_HUMAN_CONNECTOR_H_
#define CORE_SERVER_CONNECTOR_HUMAN_CONNECTOR_H_

#include <mutex>
#include "core/server/connector/connector.h"
#include "core/key_set.h"

class HumanConnector : public Connector {
public:
    virtual ~HumanConnector() {}

    virtual void send(const FrameRequest&) override;
    virtual bool receive(FrameResponse*) override;

    virtual bool isHuman() const override { return true; }
    // HumanConnector is always alive.
    virtual bool alive() const override { return true; }
    virtual void setAlive(bool flag) override;
    virtual bool pollable() const override { return false; }
    virtual int readerFd() const override;

    void setKeySet(const KeySet&);

private:
    void writeString(const std::string&);

    std::mutex mu_;
    KeySet currentKeySet_;
};

#endif
