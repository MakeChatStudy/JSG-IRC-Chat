// client.cpp

#include <WinSock2.h>
#include <iostream>
#include "../IRCCore/socketutility.h"
#include "clientlib.h"

#pragma comment(lib, "ws2_32")

int main()
{
	// WinSock2 API의 정보를 담는 구조체
	WSADATA wsa_data;
	// 연결된 서버와 통신하는 연결 소켓
	SOCKET connect_sock;

	Sleep(1000);

	std::cout << "IRC Chat 클라이언트 프로그램을 구동합니다 . . ." << std::endl;

	// WinSock2 API 라이브러리 초기화
	if (init_winsock_api(&wsa_data) == false)
	{
		return ABORTED;
	}

	// IPv4, 연결지향형, TCP 프로토콜을 사용한 소켓을 생성하고 서버와 연결
	connect_sock = make_connect_socket();
	if (connect_sock == INVALID_SOCKET)
	{
		return ABORTED;
	}

	client_chat_loop(connect_sock);

	std::cout << "클라이언트 프로그램을 종료합니다." << std::endl;

	// WinSock2 API 라이브러리 종료
	cleanup(connect_sock);
	return 0;
}

