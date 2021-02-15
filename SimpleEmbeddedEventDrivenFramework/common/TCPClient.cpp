
#ifdef WIN32
#include <WinSock2.h>
#include <ws2tcpip.h>
#elif __unix__
#else
#endif

#include <string>

using namespace std;

bool CreateTCPSocket(int& socket_fd)
{
#ifdef WIN32
	WSADATA data;
	WSAStartup(MAKEWORD(2,0),&data);
#else
#endif
	socket_fd = socket(AF_INET, SOCK_STREAM, 0);

	if (socket_fd < 0)
	{
		return false;
	}

	return true;
}

bool TCPConnect(const int socket_fd, const string& dest_ip, const unsigned short& dst_port)
{
	struct sockaddr_in dstAddr = { 0 };

	dstAddr.sin_port = htons(dst_port);
	dstAddr.sin_family = AF_INET;
	dstAddr.sin_addr.s_addr = inet_addr(dest_ip.c_str());

	if (connect(socket_fd, (struct sockaddr*)&dstAddr, sizeof(dstAddr)) != 0)
	{
		return false;
	}

	return true;
}

bool TCPSend(const int socket_fd, const byte data, const unsigned int len)
{
	return true;
}


