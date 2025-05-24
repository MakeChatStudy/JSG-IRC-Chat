// loglib.cpp

#include "loglib.h"

const int   ABORTED = -1;
const char* WSA_INIT_FAILURE_LOG = "WinSock2 라이브러리 초기화에 실패했습니다. with error = #";;
const char* WSA_INIT_SUCCESS_LOG = "WinSock2 라이브러리 초기화 완료 . . .";
const char* WSA_CLEANUP_LOG = "WinSock2 라이브러리를 종료합니다.";
const char* SUCCESS_TO_CREATE_SOCKET_LOG = "소켓 생성 성공 . . .";
const char* FAIL_TO_CREATE_SOCKET_LOG = "소켓 생성에 실패했습니다.";
const char* SUCCESS_TO_BIND_SOCKET_LOG = "소켓에 성공적으로 주소 정보를 바인딩 . . .";
const char* FAIL_TO_BIND_SOCKET_LOG = "소켓 바인딩에 실패했습니다.";
const char* SUCCESS_TO_LISTEN_SOCKET_LOG = "소켓을 성공적으로 수신 대기 상태에 배치 . . .";
const char* FAIL_TO_LISTEN_SOCKET_LOG = "소켓을 수신 대기 상태로 배치하는데 실패했습니다.";
const char* SUCCESS_TO_ACCEPT_CONNECT_LOG = "클라이언트의 연결 요청을 수용합니다.";
const char* FAIL_TO_ACCEPT_CONNECT_LOG = "클라이언트와의 연결에 실패했습니다.";
const char* SUCCESS_TO_SEND_LOG = "메세지를 보내는 데 성공했습니다.";
const char* FAIL_TO_SEND_LOG = "메세지를 보내는 데 실패했습니다.";
const char* SUCCESS_TO_RECV_LOG = "메세지를 받는 데 성공했습니다.";
const char* FAIL_TO_RECV_LOG = "메세지를 받는 데 실패했습니다.";
const char* CONNECTION_CLOSED_LOG = "연결이 종료되었습니다.";

const char* SUCCESS_TO_CONVERT_SERVER_ADDRESS = "서버 주소 변환 성공 . . .";
const char* FAIL_TO_CONVERT_SERVER_ADDRESS = "서버 주소를 변환하는데 실패했습니다.";
const char* SUCCESS_TO_CONNECT = "서버 연결 성공 . . .";
const char* FAIL_TO_CONNECT = "서버와의 연결에 실패했습니다.";

const char* FAIL_TO_FIND_ERROR_FILE = "에러 파일을 찾는데 실패했습니다.";

std::string get_wsa_error_log(const std::string& error_message)
{
	// 출력할 로그를 담는 std::string 객체
	std::string log;

	// 에러 내용 error #error_code error_type 형식으로 출력
	// ex. 메세지를 보내는 데 실패했습니다.        error #10038    WSAENOTSOCK
	log = error_message + ERROR_PRES + std::to_string(WSAGetLastError()) + '\t';
	log += read_error_message();

	return log;
}

std::string read_error_message(void)
{
	std::ifstream file;
	std::string path;
	std::string error_message;
	static const int ERROR_NAME_MAX_LEN = 64;
	char buffer[ERROR_NAME_MAX_LEN];

	path = ERROR_INFO_PATH + std::to_string(WSAGetLastError()) + TXT;
	file.open(path.c_str(), std::ios_base::in);
	if (file.is_open())
	{
		file.getline(buffer, ERROR_NAME_MAX_LEN);
		error_message = std::string(buffer);
	}
	else
	{
		std::cerr << FAIL_TO_FIND_ERROR_FILE << '\t';
	}
	return error_message;
}