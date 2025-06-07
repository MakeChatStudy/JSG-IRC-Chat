// clientlib.cpp

#include "clientlib.h"

SOCKET make_connect_socket(void)
{
	SOCKET connect_sock;
	sockaddr_in server_sock_addr;
	int result = 0;

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
	result = inet_pton(AF_INET, SERVER_IP, &server_sock_addr.sin_addr);
	if (result != 1)
	{
		std::cerr << FAIL_TO_CONVERT_SERVER_ADDRESS << ERROR_PRES << result << std::endl;
		cleanup(connect_sock);
		return INVALID_SOCKET;
	}
	else
	{
		std::cout << SUCCESS_TO_CONVERT_SERVER_ADDRESS << std::endl;
	}

	// connect_sock과 서버의 주소 정보를 바탕으로 연결
	result = connect(connect_sock, reinterpret_cast<sockaddr*>(&server_sock_addr), sizeof(sockaddr_in));
	if (result == SOCKET_ERROR)
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


int client_chat_loop(SOCKET connect_sock)
{
	// send 와 recv 함수가 성공적으로 수행되었는지를 확인하는 결과값. thread 내부에서 데이터를 전달하거나 받기전에 확인
	std::atomic<bool> connect_state(true);
	// 루프를 돌며 사용자 입력을 받아 소켓을 통해 데이터를 전송하는 쓰레드 변수
	std::thread t_send;
	std::cout << "전달할 메시지를 입력하시오(exit: \"quit\"): " << std::endl;

	// send 용 쓰레드 생성
	t_send = std::thread(client_input_loop_thread, connect_sock, std::ref(connect_state));

	client_recv_loop(connect_sock, connect_state);

	// t_send 쓰레드가 실행을 마칠 때까지 메인 쓰레드를 중지
	t_send.join();

	return 0;
}

void client_input_loop_thread(SOCKET connect_sock, std::atomic<bool>& connect_state)
{
	SocketOStream sout(connect_sock);
	static std::string nick = "Anonymous";
	std::string user_input;
	int send_result = 0;
	bool quit = false;

	// 루프를 돌며 입력받은 send_message를 소켓을 통해 전송
	// quit을 입력하거나 연결 상태가 false 혹은 send 에 실패하면 루프를 탈출
	while (send_result != SOCKET_ERROR && connect_state.load())
	{
		std::getline(std::cin, user_input);
		
		if (process_command(connect_sock, user_input, nick, quit))
		{
			if (quit) break;
		}
		else
		{
			sout << "NICK:" << nick << ", TRAILING:" << user_input << SocketOStream::CRLF;
			if (!sout) break;
		}
	}
	connect_state.store(false);
	closesocket(connect_sock);
	return;
}

void client_recv_loop(SOCKET s, std::atomic<bool>& connect_state)
{
	std::string recv_message;
	int recv_result = 0;
	// 루프를 돌며 소켓을 돌며 전달받은 메시지를 콘솔에 출력
	// 연결 상태가 false 이거나 recv 에 실패하면 루프를 탈출
	while (connect_state.load())
	{
		recv_message = recv_string(s, recv_result);
		if (connect_state.load() == false)
		{
			break;
		}
		if (recv_result <= 0)
		{
			if (recv_result < 0)
			{
				std::cerr << get_wsa_error_log(FAIL_TO_RECV_LOG) << std::endl;
			}
			std::cout << CONNECTION_CLOSED_LOG << std::endl;
			break;
		}
		std::cout << IRCMessage(recv_message) << std::endl;
	}
	connect_state.store(false);
	return;
}

void set_nick(SOCKET s, std::string& origin, const std::string& new_nick)
{
	if (new_nick.empty())
	{
		std::cout << "닉네임을 입력해주세요. Usage: nick <MYNAME>/\n";
		return ;
	}
	origin = new_nick;
	return;
}

bool process_command(SOCKET connect_sock, const std::string& user_input, std::string& nick, bool& quit)
{
	std::string command;
	std::string arg;
	std::stringstream ss(user_input);

	ss >> command;
	if (is_equal_ignore_case(command, CommandInfo::NICK_STRING))
	{
		ss >> arg;
		set_nick(connect_sock, nick, arg);
	}
	else if (is_equal_ignore_case(command, CommandInfo::QUIT_STRING))
	{
		quit = true;
	}
	else if (is_equal_ignore_case(command, CommandInfo::CLEAR_STRING))
	{
		system("cls");
	}
	else
	{
		return false;
	}
	return true;
}
