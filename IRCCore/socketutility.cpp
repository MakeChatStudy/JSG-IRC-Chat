// socketutility.cpp

#include "socketutility.h"

void cleanup(SOCKET sock)
{
	closesocket(sock);
	WSACleanup();
	std::cout << "WinSock2 라이브러리를 종료합니다." << std::endl;
}

sockaddr_in make_sockaddr_in(const int af, const unsigned short port, const unsigned long ip_address)
{
	sockaddr_in addr;
	addr.sin_family = af;
	addr.sin_port = htons(port);
	addr.sin_addr.s_addr = htonl(ip_address); // 모든 NIC의 IP 주소에 바인딩
	memset(&addr.sin_zero, 0, sizeof(addr.sin_zero));
	return addr;
}
