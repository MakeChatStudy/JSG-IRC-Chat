// clientlib.cpp

#include "clientlib.h"

SOCKET make_connect_socket(void)
{
	SOCKET connect_sock;
	sockaddr_in server_sock_addr;
	int conv_result;
	int conn_result;

	// �ش� ������ IPv4 ü�踦 ������ ���� �������̸�, TCP ���������� ����Ͽ� �����͸� �����ϵ��� ����
	connect_sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (connect_sock == INVALID_SOCKET)
	{
		std::cerr << get_wsa_error_log(FAIL_TO_CREATE_SOCKET_LOG) << std::endl;
		cleanup(connect_sock);
		return INVALID_SOCKET;
	}
	else
	{
		std::cout << SUCCESS_TO_CREATE_SOCKET_LOG << std::endl;
	}
	// ������ ������ �ּ� ������ IPv4, serverinfo.h�� ����� ������ ��Ʈ ��ȣ�� ����
	server_sock_addr = make_sockaddr_in(AF_INET, SERVER_PORT);

	// serverinfo.h�� ����� SERVER_IP ������ ��Ʈ��ũ ����Ʈ ������ ��ȯ�ϰ� server_sock_addr�� ����
	conv_result = inet_pton(AF_INET, SERVER_IP, &server_sock_addr.sin_addr);
	if (conv_result != 1)
	{
		std::cerr << FAIL_TO_CONVERT_SERVER_ADDRESS << ERROR_PRES << conv_result << std::endl;
		cleanup(connect_sock);
		return INVALID_SOCKET;
	}
	else
	{
		std::cout << SUCCESS_TO_CONVERT_SERVER_ADDRESS << std::endl;
	}

	// connect_sock�� ������ �ּ� ������ �������� ����
	conn_result = connect(connect_sock, reinterpret_cast<sockaddr*>(&server_sock_addr), sizeof(sockaddr_in));
	if (conn_result == SOCKET_ERROR)
	{
		std::cerr << get_wsa_error_log(FAIL_TO_CONNECT) << std::endl;
		cleanup(connect_sock);
		return INVALID_SOCKET;
	}
	else
	{
		std::cout << SUCCESS_TO_CONNECT << std::endl;
	}
	return connect_sock;
}

