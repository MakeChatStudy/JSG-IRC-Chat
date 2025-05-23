// server.cpp

#include <WinSock2.h>
#include <iostream>
#include "../IRCCore/loglib.h"
#include "../IRCCore/socketutility.h"
#include "../IRCCore/serverinfo.h"

#pragma comment(lib, "ws2_32")

/*
** 함수명		: make_server_listen_socket
** 설명			: 소켓을 생성하고 서버의 주소를 바인딩, 해당 소켓을 수신 대기 상태에 배치
** 인자			: void
** 반환값		: 수신 대기중인 소켓
*/
SOCKET make_server_listen_socket(void);

/*
** 함수명		: accept_clients_connect
** 설명			: 리슨 소켓을 통해 받은 연결 요청을 승낙하고 클라이언트와 연결된 소켓을 생성
** 인자			: [in] SOCKET listen_sock - 수신 대기중인 소켓
** 반환값		: 클라이언트와 연결된 소켓
*/
SOCKET accept_clients_connect(SOCKET listen_sock);

int main()
{
	WSADATA wsa_data;
	SOCKET listen_sock;
	SOCKET connect_sock;
	int result;

	std::cout << "서버 프로그램 가동 . . ." << std::endl;
	if (init_winsock_api(&wsa_data) == false)
	{
		return ABORTED;
	}
	listen_sock = make_server_listen_socket();
	if (listen_sock == SOCKET_ERROR)
	{
		return ABORTED;
	}
	std::cout << "서버 실행중 . . ." << std::endl;
	connect_sock = accept_clients_connect(listen_sock);
	if (connect_sock == INVALID_SOCKET)
	{
		return ABORTED;
	}
	
	std::string recv_message = recv_string(connect_sock, result);
	std::cout << recv_message << std::endl;

	cleanup({ listen_sock, connect_sock });
	return 0;
}

SOCKET make_server_listen_socket(void)
{
	SOCKET listen_sock;
	sockaddr_in addr;
	int result;
	// --------------------------------------------- //
	//	SOCKET WSAAPI socket(
	//    [in] int af,		// 주소 패밀리 사양 (Address Family)
	//	  [in] int type,	// 소켓의 형식 사양 
	//	  [in] int protocol	// 프로토콜
	//	);
	// 해당 프로젝트는 IPv4 체계를 따르며 종단간 신뢰성 있는 TCP 프로토콜을 사용하여 데이터를 전송하도록 규정
	listen_sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (listen_sock == INVALID_SOCKET)
	{
		std::cerr << get_wsa_error_log(FAIL_TO_CREATE_SOCKET_LOG) << std::endl;
		cleanup(listen_sock);
		return INVALID_SOCKET;
	}
	else
	{
		std::cout << SUCCESS_TO_CREATE_SOCKET_LOG << std::endl;
	}

	addr = make_sockaddr_in(AF_INET, SERVER_PORT, INADDR_ANY);
	result = bind(listen_sock, reinterpret_cast<sockaddr*>(&addr), sizeof(addr));
	if (result == SOCKET_ERROR)
	{
		std::cerr << get_wsa_error_log(FAIL_TO_BIND_SOCKET_LOG) << std::endl;
		cleanup(listen_sock);
		return SOCKET_ERROR;
	}
	else
	{
		std::cout << SUCCESS_TO_BIND_SOCKET_LOG << std::endl;
	}

	result = listen(listen_sock, SOMAXCONN);
	if (result == SOCKET_ERROR)
	{
		std::cerr << get_wsa_error_log(FAIL_TO_LISTEN_SOCKET_LOG) << std::endl;
		cleanup(listen_sock);
		return SOCKET_ERROR;
	}
	else
	{
		std::cout << SUCCESS_TO_LISTEN_SOCKET_LOG << std::endl;
	}
	return listen_sock;
}

SOCKET accept_clients_connect(SOCKET listen_sock)
{
	SOCKET connect_sock;
	sockaddr_in client_sock_addr;
	int client_size;

	client_size = sizeof(sockaddr_in);
	connect_sock = accept(listen_sock, reinterpret_cast<sockaddr*>(&client_sock_addr), &client_size);
	if (connect_sock == INVALID_SOCKET)
	{
		std::cerr << get_wsa_error_log(FAIL_TO_ACCEPT_CONNECT_LOG) << std::endl;
		cleanup({ listen_sock, connect_sock });
		return INVALID_SOCKET;
	}
	else
	{
		std::cout << SUCCESS_TO_ACCEPT_CONNECT_LOG << std::endl;
	}

	return connect_sock;
}

