#include <set>
#include <unordered_set>
#include "word.h"

#include <benchmark/benchmark.h>

static void ordered_insert(benchmark::State& state)
{
	std::set<std::string> set;
	benchmark::DoNotOptimize(set);
	Word word;
	while(state.KeepRunning())
	{
		word.Next();
		set.insert(word.Value);
	}
}

BENCHMARK(ordered_insert);


static void unordered_insert(benchmark::State& state)
{
	std::unordered_set<std::string> set;
	benchmark::DoNotOptimize(set);
	Word word;
	while(state.KeepRunning())
	{
		word.Next();
		set.insert(word.Value);
	}
}

BENCHMARK(unordered_insert);

BENCHMARK_MAIN();
