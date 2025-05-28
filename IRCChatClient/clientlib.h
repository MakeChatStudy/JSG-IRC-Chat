// clientlib.h

#pragma once

#include <WinSock2.h>
#include <WS2tcpip.h>
#include <iostream>
#include "../IRCCore/loglib.h"
#include "../IRCCore/socketutility.h"
#include "../IRCCore/serverinfo.h"

/*
** �Լ���		: make_connect_socket
** ����			: IPv4 TCP ����� �ϴ� ������ �����ϰ� ������ ����
** ����			: void
** ��ȯ��		: ������ ����� ����
*/
SOCKET make_connect_socket(void);

