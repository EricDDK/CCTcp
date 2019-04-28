#ifndef __NETWORK_NETCONFIG_H__
#define __NETWORK_NETCONFIG_H__

#include "cocos2d.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
#include <windows.h>
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_IOS || CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <errno.h>
#include <sys/syscall.h>
#include <fcntl.h>
#include <netinet/tcp.h>
#endif

enum class SocketStatus
{
	SocketCreateFailed = -2,
	SocketIoError = -1,
	SocketIoClosed = 0,
	SocketConnected = 1,
	SocketConnecting = 2,
	SocketDisconnected = 3,
	SocketConnectFailed = 4,
	SocketConnectTimeout = 5,
	SocketReceive = 6,
};

#endif // !__NETWORK_NETCONFIG_H__
