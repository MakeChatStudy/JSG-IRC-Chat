// clientlib.h

#pragma once

#include <WinSock2.h>
#include <WS2tcpip.h>
#include <iostream>
#include "../IRCCore/loglib.h"
#include "../IRCCore/socketutility.h"
#include "../IRCCore/serverinfo.h"

/*
** �Լ���		: make_server_listen_socket
** ����			: ������ �����ϰ� ������ �ּҸ� ���ε�, �ش� ������ ���� ��� ���¿� ��ġ
** ����			: void
** ��ȯ��		: ���� ������� ����
*/
SOCKET make_server_listen_socket(void);

/*
** �Լ���		: accept_clients_connect
** ����			: ���� ������ ���� ���� ���� ��û�� �³��ϰ� Ŭ���̾�Ʈ�� ����� ������ ����
** ����			: [in] SOCKET listen_sock - ���� ������� ����
** ��ȯ��		: Ŭ���̾�Ʈ�� ����� ����
*/
SOCKET accept_clients_connect(SOCKET listen_sock);