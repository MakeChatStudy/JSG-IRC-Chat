// client.cpp

#include <WinSock2.h>
#include <WS2tcpip.h>
#include <iostream>
#include "../IRCCore/loglib.h"
#include "../IRCCore/socketutility.h"
#include "../IRCCore/serverinfo.h"

#pragma comment(lib, "ws2_32")

/*
** 함수명		: make_connect_socket
** 설명			: IPv4 TCP 통신을 하는 소켓을 생성하고 서버와 연결
** 인자			: void
** 반환값		: 서버와 연결된 소켓
*/
SOCKET make_connect_socket(void);

int main()
{
	WSADATA wsa_data;
	SOCKET connect_sock;
	std::string send_message;
	int result;

	Sleep(1000);

	std::cout << "IRC Chat 클라이언트 프로그램을 구동합니다 . . ." << std::endl;
	if (init_winsock_api(&wsa_data) == false)
	{
		return ABORTED;
	}
	connect_sock = make_connect_socket();
	if (connect_sock == INVALID_SOCKET)
	{
		return ABORTED;
	}
	
	
	std::getline(std::cin, send_message);
	result = send_string(connect_sock, send_message);

	cleanup(connect_sock);
	return 0;
}

SOCKET make_connect_socket(void)
{
	SOCKET connect_sock;
	sockaddr_in server_sock_addr;
	int conv_result;
	int conn_result;

	// --------------------------------------------- //
	//	SOCKET WSAAPI socket( 
	//    [in] int af,		// 주소 패밀리 사양 (Address Family)
	//	  [in] int type,	// 소켓의 형식 사양 
	//	  [in] int protocol	// 프로토콜
	//	);
	// 해당 프로젝트는 IPv4 체계를 따르며 종단간 신뢰성 있는 TCP 프로토콜을 사용하여 데이터를 전송하도록 규정
	connect_sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (connect_sock == INVALID_SOCKET)
	{
		std::cerr << get_wsa_error_log(FAIL_TO_CREATE_SOCKET_LOG) << std::endl;
		cleanup(connect_sock);
		return INVALID_SOCKET;
	}
	else
	{
		std::cout << SUCCESS_TO_CREATE_SOCKET_LOG << std::endl;
	}
	server_sock_addr = make_sockaddr_in(AF_INET, SERVER_PORT);
	conv_result = inet_pton(AF_INET, SERVER_IP, &server_sock_addr.sin_addr);
	if (conv_result != 1)
	{
		std::cerr << FAIL_TO_CONVERT_SERVER_ADDRESS << ERROR_PRES << conv_result << std::endl;
		cleanup(connect_sock);
		return INVALID_SOCKET;
	}
	else
	{
		std::cout << SUCCESS_TO_CONVERT_SERVER_ADDRESS << std::endl;
	}
	conn_result = connect(connect_sock, reinterpret_cast<sockaddr*>(&server_sock_addr), sizeof(sockaddr_in));
	if (conn_result == SOCKET_ERROR)
	{
		std::cerr << get_wsa_error_log(FAIL_TO_CONNECT) << std::endl;
		cleanup(connect_sock);
		return INVALID_SOCKET;
	}
	else
	{
		std::cout << SUCCESS_TO_CONNECT << std::endl;
	}
	return connect_sock;
}
