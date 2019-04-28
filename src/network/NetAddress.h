#ifndef __NETWORK_NETADDRESS_H__
#define __NETWORK_NETADDRESS_H__

#include "cocos2d.h"
#include "NetConfig.h"

NS_CC_BEGIN

class NetAddress : public sockaddr_in
{
public:
	NetAddress();
	NetAddress(const struct sockaddr* addr);
	virtual ~NetAddress();

	operator const struct sockaddr*() const;
	void setIP(std::string ip);
	void setPort(int port);
	int getSize();

private:

};

NS_CC_END

#endif // ! __NETWORK_NETADDRESS_H__