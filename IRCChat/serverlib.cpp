#include "serverlib.h"

SOCKET make_server_listen_socket(void)
{
	// ���� ��� ���¿� ��ġ�� ������ ���� ����
	SOCKET listen_sock;
	// ���Ͽ� ���ε��� ������ �ּ� ����
	sockaddr_in addr;
	// �Լ��� �����, �� �Լ��� ���������� ����Ǿ������� Ȯ���ϱ� ���� ����
	int result;

	// �ش� ������ IPv4 ü�踦 ������ ���� �������̸�, TCP ���������� ����Ͽ� �����͸� �����ϵ��� ����
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

	// ������ �ּ� ������ IPv4, serverinfo.h�� ����� ������ ��Ʈ ��ȣ, ��� NIC�κ��� ������ �ޱ� ���� INADDR_ANY�� ����
	addr = make_sockaddr_in(AF_INET, SERVER_PORT, INADDR_ANY);

	// ���Ͽ� ���� �ּ� ������ ���ε�
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

	// ������ �ִ� ũ�⸦ listen ���� ť�� ����
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
	// ���� ��û�� �³��ϰ� Ŭ���̾�Ʈ�� ����� ����
	SOCKET connect_sock;
	// Ŭ���̾�Ʈ�� �ּ� ������ ���� ����ü
	sockaddr_in client_sock_addr;
	// client_sock_addr�� ����(byte)
	int client_size;

	client_size = sizeof(sockaddr_in);

	// Ŭ���̾�Ʈ�� ���� ��û �³�
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
