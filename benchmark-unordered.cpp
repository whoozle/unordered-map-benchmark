#include <unordered_set>
#include "word.h"

int main()
{
	std::unordered_set<std::string> set;
	Word word(WORDS_LIMIT);
	while(word.Next())
	{
		set.insert(word.Value);
	}
}
