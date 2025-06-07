#include "IRCMessage.h"
IRCMessage::IRCMessage()
{
	_fields.resize(FIELD_SIZE);
}

IRCMessage::IRCMessage(const std::string& message) : _raw_data(message)
{
	_fields.resize(FIELD_SIZE);
	parse(message);
}

void IRCMessage::parse(const std::string& message)
{
	int i = 0;
	int fi = 0;
	bool key_processing = true;
	std::string value = "";

	while (i + 1 < message.length())
	{
		if (message[i] == '\r' && message[i + 1] == '\n') break;

		if (key_processing)
		{
			if (message[i] == ':')
			{
				key_processing = false;
			}
		}
		else
		{
			if (message[i] == ',' && fi != (int)IRCMessage::EFieldType::TRAILING)
			{
				_fields[fi] = value;
				value = "";
				++fi;
				key_processing = true;
			}
			else
			{
				value += message[i];
			}
		}
		++i;
	}
	_fields[fi] = value;
	return;
}

const std::string& IRCMessage::getField(EFieldType f) const
{
	return _fields.at((int)f);
}

const std::string& IRCMessage::getRawMessage() const
{
	return _raw_data;
}

std::ostream& operator<<(std::ostream& os, const IRCMessage& irc_message)
{
	os << wrap_nick(irc_message.getField(IRCMessage::EFieldType::NICK)) <<
		irc_message.getField(IRCMessage::EFieldType::TRAILING);

	return os;
}

std::string wrap_nick(const std::string& nick)
{
	return '[' + nick + "]: ";
}
