// socketutility.cpp

#include "socketutility.h"

bool init_winsock_api(WSADATA* wsa_data)
{
	int init_result;

	// 프로세스에서 Winsock DLL(Ws2_32.dll)사용을 시작하기 위한 WinSock2 API 초기화 함수 호출
	init_result = WSAStartup(MAKEWORD(2, 2), wsa_data);

	if (init_result != 0)
	{
		std::cerr << WSA_INIT_FAILURE_LOG << init_result << std::endl;
		return false;
	}
	else
	{
		std::cout << WSA_INIT_SUCCESS_LOG << std::endl;
	}
	return true;
}

void cleanup(SOCKET sock)
{
	if (sock != INVALID_SOCKET)
	{
		closesocket(sock);
	}

	// Winsock 2 DLL(Ws2_32.dll)의 사용을 종료
	WSACleanup();
	std::cout << WSA_CLEANUP_LOG << std::endl;
}
void cleanup(std::initializer_list<SOCKET> sock_list)
{
	for (SOCKET s : sock_list)
	{
		if (s != INVALID_SOCKET)
		{
			closesocket(s);
		}
	}
	// Winsock 2 DLL(Ws2_32.dll)의 사용을 종료
	WSACleanup();
	std::cout << WSA_CLEANUP_LOG << std::endl;
}

sockaddr_in make_sockaddr_in(const int af, const unsigned short port, const unsigned long ip_address/* = 0*/)
{
	sockaddr_in addr;
	addr.sin_family = af;
	
	// port 매개변수를 네트워크 바이트 오더 unsinged short로 변환
	addr.sin_port = htons(port);

	// ip_address를 네트워크 바이트 오더로 변환 unsigned long
	addr.sin_addr.s_addr = htonl(ip_address);

	// 패딩 역할의 sin_zero를 0으로 초기화
	memset(&addr.sin_zero, 0, sizeof(addr.sin_zero));
	return addr;
}

int send_string(SOCKET s, const std::string& message)
{
	SOCKET sss = NULL;
	return send(sss, message.c_str(), message.length() + 1, 0);
}

std::string recv_string(SOCKET s, int& recv_result)
{
	static const int MAX_BUF_SIZE = 100;
	char char_buf[MAX_BUF_SIZE];

	recv_result = recv(s, char_buf, MAX_BUF_SIZE, 0);
	if (recv_result <= 0)
	{
		return "";
	}
	else
	{
		return std::string(char_buf);
	}
}

int chat_loop(SOCKET connect_sock)
{
	// send 와 recv 함수가 성공적으로 수행되었는지를 확인하는 결과값. thread 내부에서 데이터를 전달하거나 받기전에 확인
	bool connect_state;
	// 루프를 돌며 사용자 입력을 받아 소켓을 통해 데이터를 전송하는 쓰레드 변수
	std::thread t_send;
	// 루프를 돌며 소켓을 통해 데이터를 전달받아 콘솔에 출력하는 쓰레드 변수
	std::thread t_recv;

	connect_state = true;
	std::cout << "전달할 메시지를 입력하시오(exit: \"quit\"): " << std::endl;

	// send 용 쓰레드 생성
	t_send = std::thread(send_loop_thread, connect_sock, std::ref(connect_state));
	// recv 용 쓰레드 생성
	t_recv = std::thread(recv_loop_thread, connect_sock, std::ref(connect_state));

	// t_send 쓰레드가 실행을 마칠 때까지 메인 쓰레드를 중지
	t_send.join();
	// t_recv 쓰레드가 실행을 마칠 때까지 메인 쓰레드를 중지
	t_recv.join();

	return 0;
}

void send_loop_thread(SOCKET s, bool& connect_state)
{
	const static std::string QUIT_STRING = "quit";
	std::string send_message;
	int send_result;

	// 루프를 돌며 입력받은 send_message를 소켓을 통해 전송
	// quit을 입력하거나 연결 상태가 false 혹은 send 에 실패하면 루프를 탈출
	while (1)
	{
		std::getline(std::cin, send_message);
		if (send_message == QUIT_STRING || connect_state == false)
		{
			break;
		}
		send_result = send_string(s, send_message);
		if (send_result == SOCKET_ERROR)
		{
			std::cerr << get_wsa_error_log(FAIL_TO_SEND_LOG) << std::endl;
			break;
		}
	}
	closesocket(s);
	connect_state = false;
	return;
}

void recv_loop_thread(SOCKET s, bool& connect_state)
{
	std::string recv_message;
	int recv_result;
	// 루프를 돌며 소켓을 돌며 전달받은 메시지를 콘솔에 출력
	// 연결 상태가 false 이거나 recv 에 실패하면 루프를 탈출
	while (1)
	{
		if (connect_state == false)
		{
			break;
		}
		recv_message = recv_string(s, recv_result);
		if (recv_result <= 0)
		{
			if (recv_result < 0)
			{
				std::cerr << get_wsa_error_log(FAIL_TO_RECV_LOG) << std::endl;
			}
			else
			{
				std::cerr << CONNECTION_CLOSED_LOG << std::endl;
			}
			break;
		}
		std::cout << recv_message << std::endl;
	}
	closesocket(s);
	connect_state = false;
	return;
}