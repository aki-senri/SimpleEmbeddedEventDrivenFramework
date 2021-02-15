#include "TCPClient.h"

#include <stdio.h>
#include <string>

using namespace std;

bool CreateTCPSocket(SOCKET& socket_fd)
{
#ifdef WIN32
	WSADATA data;
	if (WSAStartup(MAKEWORD(2, 0), &data) != 0)
	{
		return false;
	}	
#else
#endif
	socket_fd = socket(AF_INET, SOCK_STREAM, 0);

	if (socket_fd < 0)
	{
		return false;
	}

	return true;
}

bool TCPConnect(const SOCKET socket_fd, const string& dest_ip, const unsigned short& dest_port)
{
	struct sockaddr_in dest_addr = { 0 };

	dest_addr.sin_port = htons(dest_port);
	dest_addr.sin_family = AF_INET;
	if (inet_pton(AF_INET, dest_ip.c_str(), &dest_addr.sin_addr.s_addr) != 1)
	{
		return false;
	}

	if (connect(socket_fd, (struct sockaddr*)&dest_addr, sizeof(dest_addr)) != 0)
	{
		return false;
	}

	return true;
}

bool TCPSend(const SOCKET socket_fd, const byte data[], const unsigned int len)
{
	if (send(socket_fd, (char*)data, len, 0) < 0)
	{
		return false;
	}
	return true;
}

bool TCPReceive(const SOCKET socket_fd, byte data[], const unsigned int len, int& recv_len)
{
	int result = recv(socket_fd, (char*)data, len, 0);

	if(result < 0)
	{
		return false;
	}

	recv_len = result;

	return true;
}

