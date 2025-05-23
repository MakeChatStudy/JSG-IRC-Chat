// socketutility.h

#pragma once

#include <iostream>
#include <WinSock2.h>
#include <thread>
#include "loglib.h"

/*
** 함수명		: init_winsock_api
** 설명			: WinSock2 API 사용을 위해 라이브러리를 초기화 하고 로그를 출력
** 인자			: WSADATA* wsa_data - WinSock2 API의 각종 데이터를 저장
** 반환값		: bool - 초기화에 실패하면 false를 반환
*/
bool init_winsock_api(WSADATA* wsa_data);

/*
** 함수명	: cleanup
** 설명		: 전달받은 소켓들을 닫고 WSACleanup을 호출하여 WinSockAPI를 정리한다.
** 인자		: [in]	std::initializer_list<SOCKET> sock_list - 닫을 소켓들을 초기자리스트 형식으로 전달
** 반환값	: void
*/
void cleanup(std::initializer_list<SOCKET> sock_list);

/*
** 함수명	: cleanup
** 설명		: 전달받은 소켓을 닫고 WSACleanup을 호출하여 WinSockAPI를 정리한다.
** 인자		: [in]	SOCKET sock: 닫을 소켓
** 반환값	: void
*/
void cleanup(SOCKET sock);

/*
** 함수명	: make_sockaddr_in
** 설명		: sockaddr_in을 만드는 과정을 네트워크 바이트 오더 변환, sockaddr_in::sin_zero의 0 초기화 등의 작업을 추상화
** 인자		: [in]	const int af - 주소 패밀리 사양
**			: [in]	const unsigned short port - 포트 넘버
**			: [in]	sockaddr_in - 소켓이 받을 IP 주소
** 반환값	: 매개변수를 통해 선언된 sockaddr_in 구조체
*/
sockaddr_in make_sockaddr_in(const int af, const unsigned short port, const unsigned long ip_address = 0);

/*
** 함수명	: send_string
** 설명		: std::string을 사용하여 send 할 수 있도록 내부 변환과정을 추상화
** 인자		: [in]	SOCKET s - 데이터를 송신할 연결된 소켓
**			: [in]	const std::string& message - 송신할 메세지
** 반환값	: int - send 함수의 리턴값
*/
int send_string(SOCKET s, const std::string& message);

/*
** 함수명	: recv_string
** 설명		: 연결된 소켓으로부터 데이터를 전달받고 std::string에 저장
** 인자		: [in]	SOCKET s - 데이터를 수신할 연결된 소켓
**			: [out]	int& out_recv_result - recv 함수의 리턴값
** 반환값	: 수신한 메세지를 담은 std::string
*/
std::string recv_string(SOCKET s, int& recv_result);