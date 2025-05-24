// clientlib.h

#pragma once

#include <WinSock2.h>
#include <WS2tcpip.h>
#include <iostream>
#include "../IRCCore/loglib.h"
#include "../IRCCore/socketutility.h"
#include "../IRCCore/serverinfo.h"

/*
** 함수명		: make_connect_socket
** 설명			: IPv4 TCP 통신을 하는 소켓을 생성하고 서버와 연결
** 인자			: void
** 반환값		: 서버와 연결된 소켓
*/
SOCKET make_connect_socket(void);

