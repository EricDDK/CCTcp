#include "SocketEngine.h"

USING_NS_CC;

SocketEngine::SocketEngine()
{

}

SocketEngine::~SocketEngine()
{

}

void SocketEngine::send(Binary* buffer)
{

}

bool SocketEngine::connect(std::string ip, int port)
{
	_address.setIP(ip);
	_address.setPort(port);
	_socket.setIPAddress(_address);
	return true;
}

