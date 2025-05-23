// socketutility.cpp

#include "socketutility.h"

bool init_winsock_api(WSADATA* wsa_data)
{
	int init_result;

	init_result = WSAStartup(MAKEWORD(2, 2), wsa_data);

	if (init_result != 0)
	{
		std::cerr << WSA_INIT_FAILURE_LOG << init_result << std::endl;
		return false;
	}
	else
	{
		std::cout << WSA_INIT_SUCCESS_LOG << std::endl;
	}
	return true;
}

void cleanup(SOCKET sock)
{
	if (sock != INVALID_SOCKET)
	{
		closesocket(sock);
	}
	WSACleanup();
	std::cout << WSA_CLEANUP_LOG << std::endl;
}
void cleanup(std::initializer_list<SOCKET> sock_list)
{
	for (SOCKET s : sock_list)
	{
		if (s != INVALID_SOCKET)
		{
			closesocket(s);
		}
	}
	WSACleanup();
	std::cout << WSA_CLEANUP_LOG << std::endl;
}

sockaddr_in make_sockaddr_in(const int af, const unsigned short port, const unsigned long ip_address/* = 0*/)
{
	sockaddr_in addr;
	addr.sin_family = af;
	addr.sin_port = htons(port);
	addr.sin_addr.s_addr = htonl(ip_address);
	memset(&addr.sin_zero, 0, sizeof(addr.sin_zero));
	return addr;
}

int send_string(SOCKET s, const std::string& message)
{
	return send(s, message.c_str(), message.length() + 1, 0);
}

std::string recv_string(SOCKET s, int& recv_result)
{
	static const int MAX_BUF_SIZE = 100;
	char char_buf[MAX_BUF_SIZE];

	recv_result = recv(s, char_buf, MAX_BUF_SIZE, 0);
	if (recv_result <= 0)
	{
		return "";
	}
	else
	{
		return std::string(char_buf);
	}
}
