// clientlib.h

#pragma once

#include <WinSock2.h>
#include <WS2tcpip.h>
#include <iostream>
#include <atomic>
#include <sstream>
#include "../IRCCore/SocketOStream.h"
#include "../IRCCore/loglib.h"
#include "../IRCCore/socketutility.h"
#include "../IRCCore/serverinfo.h"
#include "../IRCCore/IRCMessage.h"
#include "../IRCCore/CommandInfo.h"

/*
** 함수명		: make_connect_socket
** 설명			: IPv4 TCP 통신을 하는 소켓을 생성하고 서버와 연결
** 인자			: void
** 반환값		: 서버와 연결된 소켓
*/
SOCKET make_connect_socket(void);

/*
** 함수명	: client_chat_loop
** 설명		: 서버와 클라이언트가 메시지를 송수신하는 메시지 루프 함수
** 인자		: [in]	SOCKET connect_sock - 데이터를 송수신할 연결된 소켓
** 반환값	: int - 연결 접속 종료 결과 코드
*/
int client_chat_loop(SOCKET connect_sock);

/*
** 함수명	: client_input_loop_thread
** 설명		: 클라이언트 측에서 사용자 입력을 받아 처리하는 함수. 다양한 명령어 추가 예정
** 인자		: [in]	SOCKET connect_sock - 데이터를 송신할 연결된 소켓
**			: [in, out] bool& connect_state - 연결 상태를 확인하기 위한 플래그
** 반환값	: void
*/
void client_input_loop_thread(SOCKET connect_sock, std::atomic<bool>& connect_state);

/*
** 함수명	: client_recv_loop
** 설명		: 메시지 수신과 콘솔 출력을 담당하는 쓰레드 함수
** 인자		: [in]	SOCKET connect_sock - 데이터를 수신할 연결된 소켓
**			: [in, out] bool& connect_state - 연결 상태를 확인하기 위한 플래그
** 반환값	: void
*/
void client_recv_loop(SOCKET connect_sock, std::atomic<bool>& connect_state);

/*
** 함수명	: process_command
** 설명		: 메시지 수신을 담당하는 쓰레드 함수
** 인자		: [in]	SOCKET connect_sock - 서버와 연결된 소켓
**			: [in]	std::string user_input - 클라이언트 유저의 콘솔 입력
**			: [in, out]	std::string& nick - 클라이언트의 닉네임을 저장하고 있는 변수
**			: [out]	bool& quit - quit 명령을 입력한 경우 true로 변경
** 반환값	: bool - 명령어를 처리한 경우 true, 단순 전송이라면 false
*/
bool process_command(SOCKET connect_sock, const std::string& user_input, std::string& nick, bool& quit);

/*
** 함수명	: set_nick
** 설명		: 클라이언트의 닉네임을 입력한 new_nick으로 변경
** 인자		: [in] SOCKET connect_sock - 서버와 연결된 소켓
**			: [in, out] std::string& origin - 클라이언트의 닉네임을 저장하고 있는 변수
**			: [in] std::string& new_nick - 변경하려는 새로운 닉네임
** 반환값	: void
*/
void set_nick(SOCKET connect_sock, std::string& origin, const std::string& new_nick);
