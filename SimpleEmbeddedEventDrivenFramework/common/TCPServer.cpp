#include "TCPServer.h"

TCPServer::TCPServer()
{
}

TCPServer::~TCPServer()
{
	for (SOCKET socket : dest_socket_)
	{
		closesocket(socket);
	}
}

bool TCPServer::CreateSocket()
{
#ifdef WIN32
	WSADATA data;
	if (WSAStartup(MAKEWORD(2, 0), &data) != 0)
	{
		return false;
	}	
#else
#endif
	socket_ = socket(AF_INET, SOCK_STREAM, 0);

	if (socket_ < 0)
	{
		return false;
	}

	return true;
}

bool TCPServer::CloseSocket()
{
#ifdef WIN32
	int result = closesocket(socket_);
	if (result < 0)
	{
		return false;
	}

	if (WSACleanup() < 0)
	{
		return false;
	}
#else
	if (close(socket_) < 0)
	{

	}
#endif
	return true;
}

bool TCPServer::Listen(const unsigned short dest_port, int backlog)
{
	struct sockaddr_in dest_addr = { 0 };

	dest_addr.sin_port = htons(dest_port);
	dest_addr.sin_family = AF_INET;
	dest_addr.sin_addr.s_addr = ADDR_ANY;

	if (bind(socket_, (struct sockaddr*)&dest_addr, sizeof(dest_addr)) != 0)
	{
		return false;
	}

	if (listen(socket_, backlog) != 0)
	{
		return false;
	}

	return true;
}

SOCKET TCPServer::Accept()
{
	struct sockaddr_in dest_addr = { 0 };
	int addr_size = sizeof(dest_addr);
	SOCKET dest_socket;

	dest_socket = accept(socket_, (struct sockaddr*)&dest_addr, &addr_size);

	if (dest_socket > 0)
	{
		dest_socket_.push_back(dest_socket);
	}

	return dest_socket;
}

bool TCPServer::Recieve(byte recieve_data[], unsigned int& recieve_size)
{
	return false;
}

