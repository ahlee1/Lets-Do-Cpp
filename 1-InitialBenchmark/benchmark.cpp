#include "InitialBenchmark/vectortest.h"
#include <benchmark/benchmark.h>
#include <vector>

static void BM_StringCreation(benchmark::State& state) {
	std::vector<uint64_t> t =  SingleThreadVector(10);
}
// Register the function as a benchmark
BENCHMARK(BM_StringCreation);

BENCHMARK_MAIN();
//int main(int argc, char** argv)
//{
//    ::benchmark::Initialize(&argc, argv);
//    ::benchmark::RunSpecifiedBenchmarks();
//
//    std::cout << "Finish: Push any button to continue";
//    std::cin.get();
//}