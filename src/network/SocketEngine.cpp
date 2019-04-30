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
	if (_status == SocketStatus::SocketDisconnected)
	{
		_address.setIP(ip);
		_address.setPort(port);
		_socket.setIPAddress(_address);
		if (_socket.connect())
		{
			registerDisposeSocketIO();
			_status = SocketStatus::SocketConnecting;
			return true;
		}
		else
		{
			_socket.close();
			_status = SocketStatus::SocketDisconnected;
		}
	}
	return true;
}

void SocketEngine::disconnect()
{
	unregisterDisposeSocketIO();
	_socket.close();
	_status = SocketStatus::SocketDisconnected;
	onDisconnect();
}

void SocketEngine::disposeSocketIO(float dt)
{
	if (_status == SocketStatus::SocketConnecting)
	{

	}
	else if (_status == SocketStatus::SocketConnected)
	{

	}
	else
	{

	}
}

void SocketEngine::disposeRead()
{

}

void SocketEngine::disposeWrite()
{

}

void SocketEngine::registerDisposeSocketIO()
{
	if (_isSchedule)
		return;
	Director::getInstance()->getScheduler()->schedule(schedule_selector(disposeSocketIO), this, 0.0f, false);
	_isSchedule = true;
}

void SocketEngine::unregisterDisposeSocketIO()
{
	if (_isSchedule)
	{
		Director::getInstance()->getScheduler()->unschedule(schedule_selector(disposeSocketIO), this);
		_isSchedule = false;
	}
}
