#include "serverlib.h"

SOCKET make_server_listen_socket(void)
{
	// 수신 대기 상태에 배치할 서버의 리슨 소켓
	SOCKET listen_sock;
	// 소켓에 바인딩할 서버의 주소 정보
	sockaddr_in addr;
	// 함수의 결과값, 각 함수가 성공적으로 수행되었는지를 확인하기 위한 변수
	int result;

	// 해당 소켓은 IPv4 체계를 따르며 연결 지향형이며, TCP 프로토콜을 사용하여 데이터를 전송하도록 설정
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

	// 서버의 주소 정보를 IPv4, serverinfo.h에 저장된 서버의 포트 번호, 모든 NIC로부터 연결을 받기 위한 INADDR_ANY로 설정
	addr = make_sockaddr_in(AF_INET, SERVER_PORT, INADDR_ANY);

	// 소켓에 서버 주소 정보를 바인딩
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

	// 가용한 최대 크기를 listen 소켓 큐에 지정
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
	// 연결 요청을 승낙하고 클라이언트와 연결될 소켓
	SOCKET connect_sock;
	// 클라이언트의 주소 정보를 담을 구조체
	sockaddr_in client_sock_addr;
	// client_sock_addr의 길이(byte)
	int client_size;

	client_size = sizeof(sockaddr_in);

	// 클라이언트의 연결 요청 승낙
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
