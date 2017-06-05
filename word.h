#pragma once
#include <string>
#include <stdlib.h>

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
	bool Random;
	static constexpr size_t RandomChars = 8;
	static constexpr size_t NoLimit = (size_t)~0;

	Word(size_t limit = NoLimit, bool random = false): Limit(limit), Random(random)
	{
		if (random)
			Value.resize(RandomChars);
		else
			Value.reserve(5);
	}

	bool Next()
	{
		if (Limit-- == 0)
			return false;

		if (Random)
		{
			size_t n = RandomChars;
			for(size_t i = 0 ; i < n; ++i)
				Value[n] = FirstChar + (random() * size_t(LastChar - FirstChar) / RAND_MAX);
			return true;
		}

		ssize_t n = Value.size() - 1;
		while(n >= 0) {
			if (!Char::Next(&Value[n--]))
				return true;
		}
		Value = FirstChar + Value;
		return true;
	}
};
