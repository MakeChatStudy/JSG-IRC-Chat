// socketutility.cpp

#include "socketutility.h"

const int MAX_IRC_BUFF_SIZE = 512;

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
	if (s == INVALID_SOCKET)
	{
		return INVALID_SOCKET;
	}
	/*else if (message.length() >= MAX_IRC_BUFF_SIZE)
	{
		std::cout << get_wsa_error_log(OVER_MAX_IRC_BUFF_LOG) << std::endl;
		return 
	}*/
	return send(s, message.c_str(), message.length() + 1, 0);
}

std::string recv_string(SOCKET s, int& recv_result)
{
	char char_buf[MAX_IRC_BUFF_SIZE];

	recv_result = recv(s, char_buf, MAX_IRC_BUFF_SIZE, 0);
	if (recv_result <= 0)
	{
		return "";
	}
	else
	{
		return std::string(char_buf);
	}

}

bool is_equal_ignore_case(const std::string& a, const std::string& b)
{
	if (a.length() != b.length()) return false;

	for (int i = 0; i < a.length(); i++)
	{
		if (tolower(a[i]) != tolower(b[i])) return false;
	}
	return true;
}
