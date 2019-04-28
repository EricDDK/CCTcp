#ifndef __NETWORK_SOCKET_H__
#define __NETWORK_SOCKET_H__

#include "NetConfig.h"
#include "NetAddress.h"

NS_CC_BEGIN

class Socket
{
public:
	Socket();
	virtual ~Socket();
	virtual bool init();

	bool connect();
	void close();

	int read(char* buffer, int len);
	int write(char* buffer, int len);

	SocketStatus getSocketStatus();
	void setIPAddress(const NetAddress& address);

private:
	SOCKET _socket;
	NetAddress _address;

};

NS_CC_END

#endif // !__NETWORK_SOCKET_H__