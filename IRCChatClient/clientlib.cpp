// clientlib.cpp

#include "clientlib.h"

SOCKET make_connect_socket(void)
{
	SOCKET connect_sock;
	sockaddr_in server_sock_addr;
	int conv_result;
	int conn_result;

	// 해당 소켓은 IPv4 체계를 따르며 연결 지향형이며, TCP 프로토콜을 사용하여 데이터를 전송하도록 설정
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
	// 연결할 서버의 주소 정보를 IPv4, serverinfo.h에 저장된 서버의 포트 번호로 설정
	server_sock_addr = make_sockaddr_in(AF_INET, SERVER_PORT);

	// serverinfo.h에 저장된 SERVER_IP 정보를 네트워크 바이트 오더로 변환하고 server_sock_addr에 저장
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

	// connect_sock과 서버의 주소 정보를 바탕으로 연결
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

