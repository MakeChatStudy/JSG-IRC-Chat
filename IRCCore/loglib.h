// loglib.h

#pragma once
#include <WinSock2.h>
#include <iostream>
#include <string>
#include <fstream>

const std::string ERROR_INFO_PATH = "../IRCCore/error_info/";
const std::string ERROR_PRES = "\terror #";
const std::string TXT = ".txt";

// common
extern const int   ABORTED;
extern const char* WSA_INIT_FAILURE_LOG;
extern const char* WSA_INIT_SUCCESS_LOG;
extern const char* WSA_CLEANUP_LOG;
extern const char* SUCCESS_TO_CREATE_SOCKET_LOG;
extern const char* FAIL_TO_CREATE_SOCKET_LOG;
extern const char* SUCCESS_TO_SEND_LOG;
extern const char* FAIL_TO_SEND_LOG;
extern const char* SUCCESS_TO_RECV_LOG;
extern const char* FAIL_TO_RECV_LOG;
extern const char* CONNECTION_CLOSED_LOG;

// server only
extern const char* SUCCESS_TO_BIND_SOCKET_LOG;
extern const char* FAIL_TO_BIND_SOCKET_LOG;
extern const char* SUCCESS_TO_LISTEN_SOCKET_LOG;
extern const char* FAIL_TO_LISTEN_SOCKET_LOG;
extern const char* SUCCESS_TO_ACCEPT_CONNECT_LOG;
extern const char* FAIL_TO_ACCEPT_CONNECT_LOG;

// client only
extern const char* SUCCESS_TO_CONVERT_SERVER_ADDRESS;
extern const char* FAIL_TO_CONVERT_SERVER_ADDRESS;
extern const char* SUCCESS_TO_CONNECT;
extern const char* FAIL_TO_CONNECT;

/*
** 함수명		: get_wsa_error_log
** 설명			: 실패한 함수에 대한 내용과 에러코드, Windows가 제공하는 소켓 작업에 대한 오류 상태를 제공한다
** 인자			: [in]	const std::string& error_message - 출력할 에러 로그
** 반환값		: 에러 로그와 소켓 작업 오류에 대한 정보가 합쳐진 로그
*/
std::string get_wsa_error_log(const std::string& error_message = "");

/*
** 함수명		: read_error_message
** 설명			: WSAGetLastError 함술르 통해 반환된 에러 코드에 부합하는 에러 메세지를 파일로부터 읽는다.
** 인자			: void
** 반환값		: std::string - error_code.txt로부터 읽어들인 에러 메시지
*/
std::string read_error_message(void);