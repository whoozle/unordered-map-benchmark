#include "word.h"
#include <stdio.h>

int main()
{
	Word word(1000000);
	std::hash<std::string> hash;
	while(word.Next())
	{
		printf("%016lx\t%s\n", static_cast<unsigned long>(hash(word.Value)), word.Value.c_str());
	}
}
