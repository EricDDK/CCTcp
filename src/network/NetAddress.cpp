#include "NetAddress.h"

USING_NS_CC;

NetAddress::NetAddress()
{
#if( CC_TARGET_PLATFORM == CC_PLATFORM_IOS )
	sin_len = sizeof(struct sockaddr_in);
	sin_family = AF_INET;
	sin_addr.s_addr = INADDR_ANY;
	sin_port = 0;
	memset(sin_zero, 0, 8);
#endif

#if( CC_TARGET_PLATFORM == CC_PLATFORM_WIN32 )
	sin_family = AF_INET;
	sin_addr.s_addr = INADDR_ANY;
	sin_port = 0;
	memset(sin_zero, 0, 8);
#endif

#if( CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID )
	sin_family = AF_INET;
	sin_addr.s_addr = INADDR_ANY;
	sin_port = 0;
	memset(sin_zero, 0, 8);
#endif
}

NetAddress::NetAddress(const struct sockaddr* addr)
{
	memcpy(&this->sin_family, addr, sizeof(struct sockaddr));
}

NetAddress::~NetAddress()
{

}

NetAddress::operator const struct sockaddr*() const
{
#if( CC_TARGET_PLATFORM == CC_PLATFORM_WIN32 )
	return (const struct sockaddr *)(&this->sin_family);
#endif

#if( CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID )
	return (const struct sockaddr *)(&this->sin_family);
#endif

#if( CC_TARGET_PLATFORM == CC_PLATFORM_IOS )
	return (const struct sockaddr *)(&this->sin_len);
#endif
}

void NetAddress::setIP(std::string ip)
{
	sin_addr.s_addr = inet_addr(ip.c_str());
}

void NetAddress::setPort(int port)
{
	sin_port = htons(port);
}

int NetAddress::getSize()
{
	return sizeof(sockaddr_in);
}
