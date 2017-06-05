#include <set>
#include <unordered_set>
#include "word.h"

#include <benchmark/benchmark.h>

using Ordered = std::set<std::string>;
using Unordered = std::unordered_set<std::string>;

template<typename Container>
Container generate(size_t values)
{
	Word word(values);
	Container container;
	while(word.Next())
		container.insert(word.Value);
	return container;
}

static void ordered_insert(benchmark::State& state)
{
	Ordered set;
	Word word;
	while(state.KeepRunning())
	{
		word.Next();
		set.insert(word.Value);
	}
}

BENCHMARK(ordered_insert);

template<typename Container>
static void lookup_n(benchmark::State& state, size_t values)
{
	auto container = generate<Container>(values);
	Word word;
	while(state.KeepRunning())
	{
		word.Next();
		auto i = container.find(word.Value);
		benchmark::DoNotOptimize(i);
	}
}
static void ordered_lookup_small(benchmark::State& state)
{ lookup_n<Ordered>(state, 100);  }
static void ordered_lookup_large(benchmark::State& state)
{ lookup_n<Ordered>(state, 1000000);  }

BENCHMARK(ordered_lookup_small);
BENCHMARK(ordered_lookup_large);

static void unordered_insert(benchmark::State& state)
{
	std::unordered_set<std::string> set;
	Word word;
	while(state.KeepRunning())
	{
		word.Next();
		set.insert(word.Value);
	}
}

BENCHMARK(unordered_insert);

static void unordered_lookup_small(benchmark::State& state)
{ lookup_n<Unordered>(state, 100);  }
static void unordered_lookup_large(benchmark::State& state)
{ lookup_n<Unordered>(state, 1000000);  }

BENCHMARK(unordered_lookup_small);
BENCHMARK(unordered_lookup_large);

BENCHMARK_MAIN();
