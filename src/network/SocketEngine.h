#ifndef __NETWORK_SOCKETENGINE_H__
#define __NETWORK_SOCKETENGINE_H__

#include "NetConfig.h"
#include "../ccpack/Binary.h"
#include "NetAddress.h"
#include "Socket.h"

NS_CC_BEGIN

class SocketEngine : public Ref
{
public:
	SocketEngine();
	virtual ~SocketEngine();

	virtual void onReceiveMessage(Binary& buffer) = 0;
	
public:
	void send(Binary* buffer);
	bool connect(std::string ip, int port);

private:
	NetAddress _address;
	Socket _socket;
};

NS_CC_END

#endif
