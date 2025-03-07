#include <sglib.h>
#include <algorithm>

#include <benchmark/benchmark.h>
#include <random>
#include <iostream>
#include <functional>

#define TEST_DATA_SIZE 1000
using namespace sglib::algorithm;
using namespace sglib::data;

using enum PivotSelectionMode;
using enum DataType;

template <DataType _DataType, PivotSelectionMode _Mode>
static void BM_quicksort(benchmark::State& state)
{
	std::vector<int> raw_vec = TestData::Create(_DataType, TEST_DATA_SIZE);
	while (state.KeepRunning())
	{
		std::vector<int> temp_vec = raw_vec;
		QuickSort(temp_vec.begin(), temp_vec.end(), _Mode);
	}
}

template <DataType _DataType>
static void BM_stl_sort(benchmark::State& state)
{
	std::vector<int> raw_vec = TestData::Create(_DataType, TEST_DATA_SIZE);
	while (state.KeepRunning())
	{
		std::vector<int> temp_vec = raw_vec;
		std::sort(temp_vec.begin(), temp_vec.end());
	}
}

BENCHMARK(BM_quicksort<_ASC_SORTED_, FIRST>);
BENCHMARK(BM_quicksort<_ASC_SORTED_, LAST>);
BENCHMARK(BM_quicksort<_ASC_SORTED_, MIDDLE>);
BENCHMARK(BM_quicksort<_ASC_SORTED_, MEDIAN_OF_THREE>);
BENCHMARK(BM_quicksort<_ASC_SORTED_, RANDOM>);

BENCHMARK(BM_quicksort<_DESC_SORTED_, FIRST>);
BENCHMARK(BM_quicksort<_DESC_SORTED_, LAST>);
BENCHMARK(BM_quicksort<_DESC_SORTED_, MIDDLE>);
BENCHMARK(BM_quicksort<_DESC_SORTED_, MEDIAN_OF_THREE>);
BENCHMARK(BM_quicksort<_DESC_SORTED_, RANDOM>);

BENCHMARK(BM_quicksort<_DISORDER_, FIRST>);
BENCHMARK(BM_quicksort<_DISORDER_, LAST>);
BENCHMARK(BM_quicksort<_DISORDER_, MIDDLE>);
BENCHMARK(BM_quicksort<_DISORDER_, MEDIAN_OF_THREE>);
BENCHMARK(BM_quicksort<_DISORDER_, RANDOM>);

BENCHMARK(BM_stl_sort<_ASC_SORTED_>);
BENCHMARK(BM_stl_sort<_DESC_SORTED_>);
BENCHMARK(BM_stl_sort<_DISORDER_>);

int main(int argc, char** argv)
{
	std::vector<std::string> args(argv, argv + argc);
	args.push_back("--benchmark_out=benchmark_results.csv");
	args.push_back("--benchmark_out_format=csv");

	std::vector<char*> c_args;
	for (auto& arg : args)
	{
		c_args.push_back(arg.data());
	}

	int new_argc = c_args.size();
	char** new_argv = c_args.data();

	::benchmark::Initialize(&new_argc, new_argv);
	::benchmark::RunSpecifiedBenchmarks();
	::benchmark::Shutdown();
	return 0;
}