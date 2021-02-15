#pragma once

#include <string>
#ifdef WIN32
#include <WinSock2.h>
#include <ws2tcpip.h>
#elif __unix__
#else
#endif

using byte = unsigned char;
#ifndef WIN32
using SOCKET = int;
#endif

using namespace std;

bool CreateTCPSocket(SOCKET& socket_fd);
bool TCPConnect(const SOCKET socket_fd, const string& dest_ip, const unsigned short& dest_port);
bool TCPSend(const SOCKET socket_fd, const byte data[], const unsigned int len);
bool TCPReceive(const SOCKET socket_fd, byte data[], const unsigned int len, int& recv_len);
