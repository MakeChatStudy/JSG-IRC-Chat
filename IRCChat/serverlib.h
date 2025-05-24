// clientlib.h

#pragma once

#include <WinSock2.h>
#include <WS2tcpip.h>
#include <iostream>
#include "../IRCCore/loglib.h"
#include "../IRCCore/socketutility.h"
#include "../IRCCore/serverinfo.h"

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