#ifndef GLOBALS_INCLUDED
#define GLOBALS_INCLUDED

#include <chrono>
#include <mutex>

using namespace std;

#include "fundamental_types.h"

constexpr my_uint_t GLOBAL_COUNT_FULL_UPDATE_PERIOD{1000};
constexpr my_uint_t SCREEN_UPDATE_PERIOD{10'000'000'000};

// SCREEN_UPDATE_PERIOD must be an even multiple of GLOBAL_COUNT_UPDATE_PERIOD
// or we'll never do periodic updates!
static_assert(SCREEN_UPDATE_PERIOD % GLOBAL_COUNT_FULL_UPDATE_PERIOD == 0);

extern const unsigned int NUM_THREADS;
extern const chrono::time_point<chrono::steady_clock> time_of_first_update;

// These are updated infrequently enough that there's no need to
// prevent false sharing (i.e., force them to be on separate cache lines).
extern recursive_mutex global_max_min_update_count_mutex;
extern my_uint_t global_min_n;
extern my_uint_t global_max_n;
extern my_uint_t global_update_count;
extern bool global_current_update_count_printed_once;

extern recursive_mutex global_total_count_mutex;
extern my_uint_t global_total_count;

#endif
