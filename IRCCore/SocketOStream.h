#pragma once

#include <WinSock2.h>
#include <iostream>
#include <string>
#include "../IRCCore/socketutility.h"
//#include "../IRCCore/CRLF.h"

/*
** 클래스명	: SocketOStream 
** 설명		: 연결된 소켓을 대상으로 데이터를 전송하는 과정을 추상화한 클래스. ostream 과 유사한 방식으로 사용가능
** 주의		: 마지막에 꼭 CRLF::get()을 호출하여 전송해야함.
*/
class SocketOStream
{
private:
	// 연결된 소켓
	SOCKET _sock;
	// 스트림으로 들어온 데이터를 저장하고 있는 변수. CRLF가 들어오면 flush 하게됨
	std::string _buff;
	// 메시지 전송에 성공했는지 실패했는지를 확인하기 위한 플래그 변수
	bool _state = true;

	/*
	** 메소드명	: flush
	** 설명		: 소켓을 통해 버퍼의 데이터를 전송하고 버퍼의 데이터를 비움
	** 반환값	: SocketOStream& - 자기 자신을 반환
	*/
	SocketOStream& flush();

public:
	SocketOStream() : _sock(INVALID_SOCKET), _buff("") 
	{
		_buff.reserve(MAX_IRC_BUFF_SIZE);
	}
	SocketOStream(SOCKET sock) : _sock(sock), _buff("")
	{
		_buff.reserve(MAX_IRC_BUFF_SIZE);
	}
	/*
	** 메소드명	: setSocket
	** 설명		: 데이터를 전송할 소켓을 _sock 변수에 설정
	** 인자		: [in]	SOCKET sock - 데이터를 전송할 대상과 연결된 소켓
	** 반환값	: void
	*/
	void setSocket(SOCKET sock);

	/*
	** 메소드명	: bool 변환 함수
	** 설명		: 성공적으로 데이터를 전송했는지 확인하기 위한 변수 _state 값을 이용해 bool 형으로 변환
	** 반환값	: bool
	*/
	operator bool() const
	{
		return _state;
	}

	/*
	** 메소드명	: operator<< 
	** 설명		: 버퍼에 인자값을 std::string 형태로 바꾸는 오버로딩된 버전들. 현재 string, int, char 변수를 전송 가능
	** 반환값	: SocketOStream& - 자기 자신을 반환
	*/
	SocketOStream& operator<<(const std::string& v);
	SocketOStream& operator<<(const int v);
	SocketOStream& operator<<(const char v);

	/*
	** 메소드명	: operator<<
	** 설명		: 버퍼와 관계없이 인자로 받은 IRCMessage를 전송, 버퍼를 클리어
	** 인자		: [in]	const IRCMessage& irc_message - 전송할 irc message
	** 반환값	: SocketOStream& - 자기 자신을 반환
	*/
	SocketOStream& operator<<(const IRCMessage& irc_message);

	/*
	** 메소드명	: operator<<
	** 설명		: 조정자를 인자로 받아 해당 조정자의 함수를 호출하도록 함. CRLF와 같은 조정자를 출력할 때 사용됨
	** 인자		: [in]	*manipulator - 조정자 함수 포인터
	** 반환값	: SocketOStream& - 자기 자신을 반환
	*/
	SocketOStream& operator<<(SocketOStream& (*manipulator)(SocketOStream& sout));

	/*
	** 메소드명	: CRLF
	** 설명		: 버퍼에 있는 메시지에 \r\n을 추가하고 전송한 뒤 버퍼를 비움
	** 주의		: 데이터를 전송하기 위해선 마지막에 꼭 SocketOStream::CRLF 를 호출해줘야함.
	** 인자		: [in]	SocketOStream& sout - \r\n을 추가할 소켓 스트림
	** 반환값	: SocketOStream& - 인자로 받은 sout을 반환
	*/
	static SocketOStream& CRLF(SocketOStream& sout);

	/*
	** 메소드명	: clear
	** 설명		: _state
	** 주의		: 데이터를 전송하기 위해선 마지막에 꼭 SocketOStream::CRLF 를 호출해줘야함.
	** 인자		: [in]	SocketOStream& sout - \r\n을 추가할 소켓 스트림
	** 반환값	: SocketOStream& - 인자로 받은 sout을 반환
	*/
	void clear();

	/*
	** 메소드명	: canFlush
	** 설명		: Flush 할 수 있는지 확인하는 함수
	** 주의		: Flush 전에 호출해야함
	** 반환값	: Flush 가능하면 true, 불가능하면 false;
	*/
	bool canFlush() const;
};

