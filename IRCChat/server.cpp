// server.cpp

#include <WinSock2.h>
#include <iostream>
#include "../IRCCore/socketutility.h"
#include "serverlib.h"

#pragma comment(lib, "ws2_32")

int main()
{
	// WinSock2 API의 정보를 담는 구조체
	WSADATA wsa_data;
	// 클라이언트로 부터 오는 연결 요청을 수신 대기 중인 서버의 리슨 소켓
	SOCKET listen_sock;
	// 연결된 클라이언트와 통신하는 연결 소켓
	SOCKET connect_sock;

	std::cout << "서버 프로그램 가동 . . ." << std::endl;

	// WinSock2 API 라이브러리 초기화
	if (init_winsock_api(&wsa_data) == false)
	{
		return ABORTED;
	}
	// IPv4, 연결지향형, TCP 프로토콜을 사용한 수신 대기 상태의 소켓을 생성
	listen_sock = make_server_listen_socket();
	if (listen_sock == SOCKET_ERROR)
	{
		return ABORTED;
	}
	std::cout << "서버 실행중 . . ." << std::endl;

	// 클라이언트로 부터 받은 연결 요청을 승낙하고 연결된 소켓을 생성
	connect_sock = accept_clients_connect(listen_sock);
	if (connect_sock == INVALID_SOCKET)
	{
		return ABORTED;
	}

	// 서버와 클라이언트가 서로 사용자 입력값을 주고 받는 주요 루프
	chat_loop(connect_sock);

	// WinSock2 API 라이브러리 종료
	cleanup({ listen_sock, connect_sock });
	return 0;
}