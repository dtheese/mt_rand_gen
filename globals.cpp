#include <limits>
#include <thread>

using namespace std;

#include "globals.h"

const unsigned int NUM_THREADS{
                                 thread::hardware_concurrency() > 0 ?
                                 thread::hardware_concurrency()     :
                                 1
                              };

const chrono::time_point<chrono::steady_clock> time_of_first_update{chrono::steady_clock::now()};

recursive_mutex global_max_min_update_count_mutex;
my_uint_t global_min_n{numeric_limits<my_uint_t>::max()};
my_uint_t global_max_n{0};
my_uint_t global_update_count{0};
bool global_current_update_count_printed_once{false};

recursive_mutex global_total_count_mutex;
my_uint_t global_total_count{0};
