// socketutility.cpp

#include "socketutility.h"

void cleanup(SOCKET sock)
{
	closesocket(sock);
	WSACleanup();
	std::cout << "WinSock2 ���̺귯���� �����մϴ�." << std::endl;
}

sockaddr_in make_sockaddr_in(const int af, const unsigned short port, const unsigned long ip_address)
{
	sockaddr_in addr;
	addr.sin_family = af;
	addr.sin_port = htons(port);
	addr.sin_addr.s_addr = htonl(ip_address); // ��� NIC�� IP �ּҿ� ���ε�
	memset(&addr.sin_zero, 0, sizeof(addr.sin_zero));
	return addr;
}
