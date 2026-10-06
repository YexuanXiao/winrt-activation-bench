#include <benchmark/benchmark.h>
#include <string_view>
#include <algorithm>
#include <array>
#include <random>
#include <iterator>
#include <cstddef>

#if BENCH_32
#include "data_32.inc"
#elif BENCH_64
#include "data_64.inc"
#elif BENCH_219
#include "data_219.inc"
#endif

__declspec(noinline) void* empty_make() { return nullptr; }

void* original_lookup(std::wstring_view const& name) {
    auto requal = [](std::wstring_view const& left, std::wstring_view const& right) noexcept {
        return std::equal(left.rbegin(), left.rend(), right.rbegin(), right.rend());
    };

#define WINRT_IF(func, str) if (requal(name, str)) { return func(); }
    WINRT_ACTIVATION_TABLE(WINRT_IF)

    return nullptr;
}
void* binary_lookup(std::wstring_view const& name) {
    static constexpr std::wstring_view names[] = {
#define WINRT_NAME(func, str) str,
        WINRT_ACTIVATION_TABLE(WINRT_NAME)
    };

    using make_t = void* (*)();
    static constexpr make_t makes[] = {
#define WINRT_FUNC(func, str) func,
        WINRT_ACTIVATION_TABLE(WINRT_FUNC)
    };

    auto it = std::lower_bound(std::begin(names), std::end(names), name);
    if (it != std::end(names) && *it == name) {
        return makes[it - std::begin(names)]();
    }
    return nullptr;
}

static constexpr std::wstring_view probe[] = {
#define WINRT_PROBE(func, str) str,
    WINRT_ACTIVATION_TABLE(WINRT_PROBE)
};

static void BM_Original(benchmark::State& state) {
    std::array<std::wstring_view, std::size(probe)> buf;
    std::copy(std::begin(probe), std::end(probe), buf.begin());
    std::mt19937 rng(12345);
    std::shuffle(buf.begin(), buf.end(), rng);

    for (auto _ : state) {
        for (auto const& n : buf) {
            auto r = original_lookup(n);
            benchmark::DoNotOptimize(r);
        }
    }
}
BENCHMARK(BM_Original);

static void BM_Binary(benchmark::State& state) {
    std::array<std::wstring_view, std::size(probe)> buf;
    std::copy(std::begin(probe), std::end(probe), buf.begin());
    std::mt19937 rng(12345);
    std::shuffle(buf.begin(), buf.end(), rng);

    for (auto _ : state) {
        for (auto const& n : buf) {
            auto r = binary_lookup(n);
            benchmark::DoNotOptimize(r);
        }
    }
}
BENCHMARK(BM_Binary);

BENCHMARK_MAIN();