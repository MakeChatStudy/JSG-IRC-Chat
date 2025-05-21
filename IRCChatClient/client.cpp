// client.cpp

#include <WinSock2.h>
#include <WS2tcpip.h>
#include <iostream>
#include "../IRCCore/loglib.h"
#include "../IRCCore/socketutility.h"
#include "../IRCCore/serverinfo.h"

#pragma comment(lib, "ws2_32")
int main()
{
	std::cout << "IRC Chat 클라이언트 프로그램을 구동합니다 . . ." << std::endl;

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
	SOCKET sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (sock == INVALID_SOCKET)
	{
		std::cerr << get_wsa_error_log(FAIL_TO_CREATE_SOCKET_LOG) << std::endl;
		cleanup(sock);
		return -1;
	}
	else
	{
		std::cout << SUCCESS_TO_CREATE_SOCKET_LOG << std::endl;
	}
	sockaddr_in server_sock_addr = make_sockaddr_in(AF_INET, SERVER_PORT);
	int conv_result = inet_pton(AF_INET, SERVER_IP, &server_sock_addr.sin_addr);
	if (conv_result != 1)
	{
		std::cerr << FAIL_TO_CONVERT_SERVER_ADDRESS << ERROR_PRES << conv_result << std::endl;
		cleanup(sock);
		return -1;
	}
	else
	{
		std::cout << SUCCESS_TO_CONVERT_SERVER_ADDRESS << std::endl;
	}

	int conn_result = connect(sock, reinterpret_cast<sockaddr*>(&server_sock_addr), sizeof(sockaddr_in));
	if (conn_result == SOCKET_ERROR)
	{
		std::cerr << get_wsa_error_log(FAIL_TO_CONNECT) << std::endl;
		cleanup(sock);
		return -1;
	}
	else
	{
		std::cout << SUCCESS_TO_CONNECT << std::endl;
	}
	// --------------------------------------------- //
	cleanup(sock);

	return 0;
}