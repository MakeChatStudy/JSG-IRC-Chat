// server.cpp

#include <WinSock2.h>
#include <WS2tcpip.h>
#include <iostream>
#include "../IRCCore/loglib.h"
#include "../IRCCore/socketutility.h"
#include "../IRCCore/serverinfo.h"

#pragma comment(lib, "ws2_32")
int main()
{
	std::cout << "서버 프로그램 가동 . . ." << std::endl;

	WSADATA wsa_data;
	int init_result = WSAStartup(MAKEWORD(2, 2), &wsa_data);

	if (init_result != 0)
	{
		std::cerr << WSA_INIT_FAILURE_LOG << init_result << std::endl;
		return -1;
	}
	else
	{
		std::cout << WSA_INIT_SUCCESS_LOG << std::endl;
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
		std::cerr << get_wsa_error_log(FAIL_TO_CREATE_SOCKET_LOG) << std::endl;
		cleanup(listen_sock);
		return -1;
	}
	else
	{
		std::cout << SUCCESS_TO_CREATE_SOCKET_LOG << std::endl;
	}

	sockaddr_in addr = make_sockaddr_in(AF_INET, SERVER_PORT, INADDR_ANY);
	int bind_result = bind(listen_sock, reinterpret_cast<sockaddr*>(&addr), sizeof(addr));
	if (bind_result == SOCKET_ERROR)
	{
		std::cerr << get_wsa_error_log(FAIL_TO_BIND_SOCKET_LOG) << std::endl;
		cleanup(listen_sock);
		return -1;
	}
	else
	{
		std::cout << SUCCESS_TO_BIND_SOCKET_LOG << std::endl;
	}

	int listen_result = listen(listen_sock, SOMAXCONN);
	if (listen_result == SOCKET_ERROR)
	{
		std::cerr << get_wsa_error_log(FAIL_TO_LISTEN_SOCKET_LOG) << std::endl;
		cleanup(listen_sock);
		return -1;
	}
	else
	{
		std::cout << SUCCESS_TO_LISTEN_SOCKET_LOG << std::endl;
	}
	std::cout << "서버 실행중 . . ." << std::endl;

	sockaddr_in client_sock_addr;
	int client_size = sizeof(sockaddr_in);
	SOCKET client_sock = accept(listen_sock, reinterpret_cast<sockaddr*>(&client_sock_addr), &client_size);
	if (client_sock == INVALID_SOCKET)
	{
		std::cerr << get_wsa_error_log(FAIL_TO_ACCEPT_CONNECT_LOG) << std::endl;
		cleanup(listen_sock);
		return -1;
	}
	else
	{
		std::cout << SUCCESS_TO_ACCEPT_CONNECT_LOG << std::endl;
	}
	// --------------------------------------------- //
	cleanup(listen_sock);

	return 0;
}


