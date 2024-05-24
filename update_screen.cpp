#include <chrono>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <mutex>
#include <numeric>
#include <string>

using namespace std;

#include "fundamental_types.h"
#include "globals.h"

#include "update_screen.h"

namespace
{
   mutex console_mutex;
}

void update_screen()
{
   lock_guard<mutex> lg_console_mutex{console_mutex};

   lock_guard<recursive_mutex> lg_global_max_min_update_count_mutex{
                                         global_max_min_update_count_mutex
                                                                   };

   lock_guard<recursive_mutex> lg_global_total_count_mutex{
                                         global_total_count_mutex
                                                          };

   my_uint_t max_diff{numeric_limits<my_uint_t>::max() - global_max_n};
   long double global_total_count_ld{static_cast<long double>(global_total_count)};

   long double expected_update_count{
                                       log(global_total_count_ld) + 0.57721L +
                                       (
                                          global_total_count > 50 ?
                                          0.0L                    :
                                          1.0L / (2.0L * global_total_count_ld)
                                       )
                                    };

   chrono::time_point<chrono::steady_clock> time_of_current_update{
                                                 chrono::steady_clock::now()
                                                                  };

   auto ticks_taken{time_of_current_update - time_of_first_update};
   constexpr long double tick_interval{decltype(ticks_taken)::period::den};

   long double time_taken_s{static_cast<long double>(ticks_taken.count()) / tick_interval};
   long double time_taken_h{time_taken_s / 3600.0L};

   long double rate{static_cast<long double>(global_total_count) / time_taken_s};

   if (global_current_update_count_printed_once)
      cout << endl;
   else
      cout << "\33[2K\r";

   cout << "total=" << global_total_count << ","
        << "actual_updates=" << global_update_count << ","
        << fixed << setprecision(2) << "expected_updates=" << expected_update_count << ","
        << "min=" << "\033[1m" << global_min_n << "\033[0m" << ","
        << "max=" << global_max_n << ","
        << "max_diff=" << "\033[1m" << max_diff << "\033[0m" << ","
        << fixed << setprecision(2) << time_taken_h << " hours,"
        << fixed << setprecision(0) << rate << "/s"
        << flush;

   global_current_update_count_printed_once = false;
}
