#include <set>
#include <unordered_set>
#include "word.h"

#include <benchmark/benchmark.h>

template<typename Container>
Container generate(size_t values)
{
	Word word(values);
	Container container;
	while(word.Next())
		container.insert(word.Value);
	return container;
}

template<typename Container>
static void insert(benchmark::State& state)
{
	Container set;
	Word word;
	while(state.KeepRunning())
	{
		word.Next();
		set.insert(word.Value);
	}
}

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


using Ordered = std::set<std::string>;


static void ordered_insert(benchmark::State& state)
{ insert<Ordered>(state); }
BENCHMARK(ordered_insert);

static void ordered_lookup_small(benchmark::State& state)
{ lookup_n<Ordered>(state, 100);  }
BENCHMARK(ordered_lookup_small);

static void ordered_lookup_large(benchmark::State& state)
{ lookup_n<Ordered>(state, 1000000);  }
BENCHMARK(ordered_lookup_large);


using Unordered = std::unordered_set<std::string>;


static void unordered_insert(benchmark::State& state)
{ insert<Unordered>(state); }
BENCHMARK(unordered_insert);

static void unordered_lookup_small(benchmark::State& state)
{ lookup_n<Unordered>(state, 100);  }
BENCHMARK(unordered_lookup_small);

static void unordered_lookup_large(benchmark::State& state)
{ lookup_n<Unordered>(state, 1000000);  }
BENCHMARK(unordered_lookup_large);

BENCHMARK_MAIN();
