#pragma once
#include <string>

static constexpr char FirstChar = ' ';
static constexpr char LastChar = 0x7f;

struct Char
{
	static bool Next(char *Value)
	{
		if (++*Value == LastChar)
		{
			*Value = FirstChar;
			return true;
		}
		else
			return false;
	}
};

struct Word
{
	std::string Value;
	size_t Limit;

	Word(size_t limit = (size_t)~0): Limit(limit)
	{
		Value.reserve(5);
	}

	bool Next()
	{
		if (Limit-- == 0)
			return false;

		ssize_t n = Value.size() - 1;
		while(n >= 0) {
			if (!Char::Next(&Value[n--]))
				return true;
		}
		Value = FirstChar + Value;
		return true;
	}
};
