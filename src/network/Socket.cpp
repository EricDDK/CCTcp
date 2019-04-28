#include "Socket.h"

USING_NS_CC;

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
static bool s_isWinSocketInit = false;
#endif

Socket::Socket()
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
	if (!s_isWinSocketInit)
	{
		WSADATA wsaData;
		WSAStartup(MAKEWORD(2, 0), &wsaData);
		s_isWinSocketInit = true;
	}
#endif
}

Socket::~Socket()
{
	close();
}

bool Socket::init()
{
	if (_socket != INVALID_SOCKET)
		close();
	_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (_socket == INVALID_SOCKET)
		return false;
#if( CC_TARGET_PLATFORM == CC_PLATFORM_WIN32 )
	unsigned long ul = 1;
	int nRet = ioctlsocket(_socket, FIONBIO, (unsigned long*)&ul);
	if (nRet == SOCKET_ERROR)
	{
		close();
		return false;
	}
#endif
#if( CC_TARGET_PLATFORM == CC_PLATFORM_IOS || CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID )
	int nFlags = fcntl(_socket, F_GETFL, 0);
	int nRet = fcntl(_socket, F_SETFL, nFlags | O_NONBLOCK);
	if (nRet == SOCKET_ERROR)
	{
		close();
		return false;
	}
#endif
	int nNoDelay = 1;
	if (setsockopt(_socket, IPPROTO_TCP, TCP_NODELAY, (char*)&nNoDelay, sizeof(nNoDelay)) == SOCKET_ERROR)
	{
		close();
		return false;
	}
	return true;
}

bool Socket::connect()
{
	if (_socket == INVALID_SOCKET)
	{
		if (!init())
			return false;
	}
	int nRet = ::connect(_socket, _address, _address.getSize());
	if (nRet == 0)
		return true;
	else
	{
		{
#if( CC_TARGET_PLATFORM == CC_PLATFORM_WIN32 )
			int nError = WSAGetLastError();
			if (nError == WSAEWOULDBLOCK)
				return true;
			else
				return false;
#endif

#if( CC_TARGET_PLATFORM == CC_PLATFORM_IOS || CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID )
			if (nRet == SOCKET_ERROR && errno == EINPROGRESS)
				return true;
			else
				return false;
#endif
		}
		return false;
	}
}

void Socket::close()
{
	if (_socket != INVALID_SOCKET)
	{
#if( CC_TARGET_PLATFORM == CC_PLATFORM_WIN32 )
		closesocket(_socket);
#endif

#if( CC_TARGET_PLATFORM == CC_PLATFORM_IOS || CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID )
		close(_socket);
#endif
		_socket = INVALID_SOCKET;
	}
}

int Socket::read(char* buffer, int len)
{
	if (_socket == INVALID_SOCKET)
		return (int)SocketStatus::SocketIoError;
	return ::recv(_socket, buffer, len, 0);
}

int Socket::write(char* buffer, int len)
{
	if (_socket == INVALID_SOCKET)
		return (int)SocketStatus::SocketIoError;
#if( CC_TARGET_PLATFORM == CC_PLATFORM_WIN32 || CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID )
	return ::send(_socket, buffer, len, 0);
#endif

#if( CC_TARGET_PLATFORM == CC_PLATFORM_IOS )
	return ::send(_socket, buffer, len, SO_NOSIGPIPE);
#endif
}

SocketStatus Socket::getSocketStatus()
{
	fd_set	fd;
	struct timeval tv;
	FD_ZERO(&fd);
	FD_SET(_socket, &fd);
	tv.tv_sec = 0;
	tv.tv_usec = 0;

	if (select((int)(_socket + 1), NULL, &fd, NULL, &tv) > 0)
	{
		if (FD_ISSET(_socket, &fd))
		{
#if( CC_TARGET_PLATFORM == CC_PLATFORM_WIN32 )
			return SocketStatus::SocketConnected;
#elif( CC_TARGET_PLATFORM == CC_PLATFORM_IOS || CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID )
			int nError;
			socklen_t len = sizeof(nError);
			if (getsockopt(_socket, SOL_SOCKET, SO_ERROR, &nError, &len) < 0)
				return SocketStatus::SocketConnectFailed;
			if (nError == ECONNREFUSED || nError == ETIMEDOUT)
				return SocketStatus::SocketConnectFailed;
			return SocketStatus::SocketConnected;
#endif
		}
	}
	return SocketStatus::SocketConnecting;
}

void Socket::setIPAddress(const NetAddress& address)
{
	_address = address;
}
