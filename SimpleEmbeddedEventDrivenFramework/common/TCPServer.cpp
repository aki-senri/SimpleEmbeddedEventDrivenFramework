#include "TCPServer.h"
#include "Timer.h"
#include <memory>

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

void TCPServer::SetMaxClient(unsigned int max)
{
	max_client_ = max;
}

void TCPServer::SetMaxBufferSize(unsigned int max)
{
	max_buffer_size_ = max;
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

	return dest_socket;
}

bool TCPServer::Recieve(SOCKET socket, byte recieve_data[], const unsigned int recieve_max, unsigned int& recieve_size)
{
	int result = recv(socket, (char*)recieve_data, recieve_max, 0);

	if (result < 0)
	{
		return false;
	}

	recieve_size = result;

	return true;
}

bool TCPServer::RecieveBySocketIndex(size_t socket_index, byte recieve_data[], const unsigned int recieve_max, unsigned int& recieve_size)
{
	if (dest_socket_.size() < socket_index)
	{
		return false;
	}

	return Recieve(dest_socket_.at(socket_index), recieve_data, recieve_max, recieve_size);
}

bool TCPServer::StartListener(const unsigned short dest_port)
{
	byte *recieve_buffer = new byte[max_buffer_size_];
	unsigned int recieve_size = 0;
	
	listner_running_ = true;
	while (listner_running_)
	{
		if (Recieve(socket_, recieve_buffer, max_buffer_size_, recieve_size))
		{
			RecieveFunction(recieve_buffer, recieve_size);
		}
	}

	delete[] recieve_buffer;

	return false;
}

bool TCPServer::StopListner()
{
	if (listner_running_)
	{
		listner_running_ = false;
		Timer thread_abort_timer;
	}

	return false;
}

bool TCPServer::StopListner(unsigned int index)
{
	if (listner_running_)
	{
		listner_running_ = false;
		Timer thread_abort_timer;
	}

	return false;
}

