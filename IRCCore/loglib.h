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
extern const char* WSA_INIT_FAILURE_LOG;
extern const char* WSA_INIT_SUCCESS_LOG;
extern const char* SUCCESS_TO_CREATE_SOCKET_LOG;
extern const char* FAIL_TO_CREATE_SOCKET_LOG;

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

std::string get_wsa_error_log(const std::string& error_message = "");

