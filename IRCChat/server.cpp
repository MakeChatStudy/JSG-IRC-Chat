#include <WinSock2.h>
#include <WS2tcpip.h>
#include <iostream>

#pragma comment(lib, "ws2_32")

void cleanup(SOCKET sock);

int main()
{
	enum { CHAT_PORT_NUMBER = 5150 };
	std::cout << "server program" << std::endl;

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
	//	SOCKET WSAAPI socket(
	//    [in] int af,		// 주소 패밀리 사양 (Address Family)
	//	  [in] int type,	// 소켓의 형식 사양 
	//	  [in] int protocol	// 프로토콜
	//	);
	// 해당 프로젝트는 IPv4 체계를 따르며 종단간 신뢰성 있는 TCP 프로토콜을 사용하여 데이터를 전송하도록 규정
	SOCKET listen_sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (listen_sock == INVALID_SOCKET)
	{
		std::cerr << "socket function failed with error = " << WSAGetLastError() << std::endl;
		cleanup(listen_sock);
		return -1;
	}
	else
	{
		std::cout << "Succeded to socket function()" << std::endl;
	}

	sockaddr_in addr;
	addr.sin_family = AF_INET;
	addr.sin_port = htons(CHAT_PORT_NUMBER);
	addr.sin_addr.s_addr = htonl(INADDR_ANY); // 모든 NIC의 IP 주소에 바인딩합니다
	memset(&addr.sin_zero, 0, sizeof(addr.sin_zero));
	int bind_result = bind(listen_sock, reinterpret_cast<sockaddr*>(&addr), sizeof(addr));
	if (bind_result == SOCKET_ERROR)
	{
		std::cerr << "bind function failed with error = " << WSAGetLastError() << std::endl;
		cleanup(listen_sock);
		return -1;
	}
	else
	{
		std::cout << "Succeded to bind function()" << std::endl;
	}

	int listen_result = listen(listen_sock, SOMAXCONN);
	if (listen_result == SOCKET_ERROR)
	{
		std::cerr << "listen function failed with error = " << WSAGetLastError() << std::endl;
		cleanup(listen_sock);
		return -1;
	}
	else
	{
		std::cout << "Succeded to listen function()" << std::endl;
	}
	std::cout << "Running Server . . ." << std::endl;
	// --------------------------------------------- //
	cleanup(listen_sock);
	std::cout << "WSACleanup, Quiting" << std::endl;

	return 0;
}

void cleanup(SOCKET sock)
{
	closesocket(sock);
	WSACleanup();
}
