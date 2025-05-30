#pragma once

#include <iostream>
#include <vector>
#include <string>

 /*
 ** 클래스명	: IRCMessage
 ** 설명		: std::string을 파싱하여 각 필드별 데이터를 저장하여 관리하는 클래스
 */
class IRCMessage
{
private:
	std::vector<std::string> _fields;
	std::string _raw_data;
	void parse(const std::string& message);

public:
	enum class EFieldType : int
	{
		NICK, TRAILING
	};
	enum
	{
		FIELD_SIZE = 2
	};

	IRCMessage();
	explicit IRCMessage(const std::string& message);

	const std::string& getField(EFieldType f) const;
	const std::string& getRawMessage() const;
	friend std::ostream& operator<<(std::ostream& os, const IRCMessage& irc_message);
};

std::string wrap_nick(const std::string& nick);