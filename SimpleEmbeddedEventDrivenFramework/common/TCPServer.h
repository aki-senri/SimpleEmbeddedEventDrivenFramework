#pragma once

#include <string>
#include <vector>
#ifdef WIN32
#include <WinSock2.h>
#include <ws2tcpip.h>
#include <Windows.h>
#elif __unix__
#else
#endif

using byte = unsigned char;
#ifndef WIN32
using SOCKET = int;
#endif

class TCPServer
{
public:
	TCPServer::TCPServer();
	TCPServer::~TCPServer();

	bool CreateSocket();
	bool CloseSocket();

	bool Listen(const unsigned short dest_port, int backlog = SOMAXCONN);
	SOCKET Accept();
	bool Recieve(SOCKET socket, byte recieve_data[], const unsigned int recieve_max, unsigned int& recieve_size);
	bool Recieve(size_t socket_index, byte recieve_data[], const unsigned int recieve_max, unsigned int& recieve_size);

private:
	SOCKET socket_;
	std::vector<SOCKET> dest_socket_;

};