#include "SocketOStream.h"

void SocketOStream::setSocket(SOCKET sock)
{
    _sock = sock;
}

SocketOStream& SocketOStream::operator<<(const std::string& v)
{
    _buff += v;
    return *this;
}

SocketOStream& SocketOStream::operator<<(const int v)
{
    _buff += std::to_string(v);
    return *this;
}

SocketOStream& SocketOStream::operator<<(const char v)
{
    _buff += v;
    return *this;
}

SocketOStream& SocketOStream::operator<<(const IRCMessage& irc_message)
{
    _buff += irc_message.getRawMessage();
    flush();
    return *this;
}
SocketOStream& SocketOStream::operator<<(SocketOStream& (*manipulator)(SocketOStream& sout))
{
    return manipulator(*this);
}
SocketOStream& SocketOStream::CRLF(SocketOStream& sout)
{
     const static std::string CRLF_STRING = "\r\n";
     sout._buff += CRLF_STRING;
     sout.flush();
     return sout;
}

void SocketOStream::clear()
{
    _state = true;
}

bool SocketOStream::canFlush() const
{
    if (_sock == INVALID_SOCKET)
    {
        std::cerr << get_wsa_error_log(INVALID_SOCKET_LOG) << std::endl;
    }
    else if (_buff.empty())
    {
        std::cout << "전송하려는 메시지를 입력해주세요: " << std::endl;
    }
    else if (_buff.length() >= MAX_IRC_BUFF_SIZE)
    {
        std::cerr << "전송하려는 데이터의 크기가 너무 큽니다." << std::endl;
    }
    else
    {
        return true;
    }
    return false;
}

SocketOStream& SocketOStream::flush()
{
    if (!canFlush())
    {
        _state = false;
        return *this;
    }

    _state = send_string(_sock, _buff);
    if (_state)
    {
        _buff.clear();
    }
    else
    {
        std::cout << get_wsa_error_log(FAIL_TO_SEND_LOG) << std::endl;
    }
    return *this;
}
