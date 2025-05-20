#include <WinSock2.h>
#include <WS2tcpip.h>
#include <iostream>
#pragma comment(lib, "ws2_32")

int main()
{
	WSADATA wsa_data;
	int init_result = WSAStartup(MAKEWORD(2, 2), &wsa_data);

	if (init_result != 0)
	{
		std::cerr << "error: " << init_result << "\tCan't Initialize winsock! Quiting" << std::endl;
		return -1;
	}
	else
	{
		std::cout << "Succeded to Initialize winsock" << std::endl;
	}
	// --------------------------------------------- //
	// 
	// --------------------------------------------- //
	WSACleanup();
	std::cout << "WSACleanup, Quiting" << std::endl;

	return 0;
}