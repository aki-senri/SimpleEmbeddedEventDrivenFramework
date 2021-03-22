#pragma once

#include <string>
#include <vector>
#include <thread>
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

	struct ListnerInfo
	{
		SOCKET socket;
		bool listner_running_ = false;
		std::thread thread;
	};

	bool CreateSocket();
	bool CloseSocket();

	void SetMaxClient(unsigned int max);
	void SetMaxBufferSize(unsigned int max);

	bool Listen(const unsigned short dest_port, int backlog = SOMAXCONN);
	SOCKET Accept();
	bool Recieve(SOCKET socket, byte recieve_data[], const unsigned int recieve_max, unsigned int& recieve_size);
	bool RecieveBySocketIndex(size_t socket_index, byte recieve_data[], const unsigned int recieve_max, unsigned int& recieve_size);

	bool StartListener(const unsigned short dest_port);
	bool StopListner();
	bool StopListner(unsigned int index);

private:
	SOCKET socket_;
	std::vector<SOCKET> dest_socket_;
	std::vector<ListnerInfo> listner_;

	unsigned int max_client_ = 0;
	unsigned int max_buffer_size_ = 0;

	bool listner_running_ = false;

	virtual void RecieveFunction(byte recieve_buffer[], const unsigned int recieve_size) = 0;

};