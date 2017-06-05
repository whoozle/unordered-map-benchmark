#include <set>
#include <unordered_set>
#include "word.h"
#include "hash.h"

#include <benchmark/benchmark.h>

using HashType = naive_hash<std::string>;
//using HashType = mul_shift_hash<std::string>;
//using HashType = python_hash<std::string>;

template<typename Container>
Container generate(size_t values, bool random = false)
{
	Word word(values, random);
	Container container;
	while(word.Next())
		container.insert(word.Value);
	return container;
}

template<typename Container>
static void insert(benchmark::State& state, bool random = false)
{
	Container set;
	Word word(Word::NoLimit, random);
	while(state.KeepRunning())
	{
		word.Next();
		set.insert(word.Value);
	}
}

template<typename Container>
static void lookup_n(benchmark::State& state, size_t values, bool random = false)
{
	auto container = generate<Container>(values);
	Word word(Word::NoLimit, random);
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

static void ordered_insert_random(benchmark::State& state)
{ insert<Ordered>(state, true); }
BENCHMARK(ordered_insert_random);

static void ordered_lookup_small_random(benchmark::State& state)
{ lookup_n<Ordered>(state, 100, true);  }
BENCHMARK(ordered_lookup_small_random);

static void ordered_lookup_large_random(benchmark::State& state)
{ lookup_n<Ordered>(state, 1000000, true);  }
BENCHMARK(ordered_lookup_large_random);


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

static void unordered_insert_random(benchmark::State& state)
{ insert<Unordered>(state, true); }
BENCHMARK(unordered_insert_random);

static void unordered_lookup_small_random(benchmark::State& state)
{ lookup_n<Unordered>(state, 100, true);  }
BENCHMARK(unordered_lookup_small_random);

static void unordered_lookup_large_random(benchmark::State& state)
{ lookup_n<Unordered>(state, 1000000, true);  }
BENCHMARK(unordered_lookup_large_random);


using CustomUnordered = std::unordered_set<std::string, HashType>;


static void custom_unordered_insert(benchmark::State& state)
{ insert<CustomUnordered>(state); }
BENCHMARK(custom_unordered_insert);

static void custom_unordered_lookup_small(benchmark::State& state)
{ lookup_n<CustomUnordered>(state, 100);  }
BENCHMARK(custom_unordered_lookup_small);

static void custom_unordered_lookup_large(benchmark::State& state)
{ lookup_n<CustomUnordered>(state, 1000000);  }
BENCHMARK(custom_unordered_lookup_large);

static void custom_unordered_insert_random(benchmark::State& state)
{ insert<CustomUnordered>(state, true); }
BENCHMARK(custom_unordered_insert_random);

static void custom_unordered_lookup_small_random(benchmark::State& state)
{ lookup_n<CustomUnordered>(state, 100, true);  }
BENCHMARK(custom_unordered_lookup_small_random);

static void custom_unordered_lookup_large_random(benchmark::State& state)
{ lookup_n<CustomUnordered>(state, 1000000, true);  }
BENCHMARK(custom_unordered_lookup_large_random);


BENCHMARK_MAIN();
