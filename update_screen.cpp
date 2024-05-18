#include <chrono>
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
   lock_guard<recursive_mutex> lg_global_max_min_update_count_mutex{global_max_min_update_count_mutex};
   lock_guard<recursive_mutex> lg_global_total_count_mutex{global_total_count_mutex};

   my_uint_t max_diff{numeric_limits<my_uint_t>::max() - global_max_n};

   chrono::time_point<chrono::steady_clock> time_of_current_update{chrono::steady_clock::now()};
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
        << "updates=" << global_update_count << ","
        << "min=" << global_min_n << ","
        << "max=" << max_diff << ","
        << fixed << setprecision(2) << time_taken_h << " hours,"
        << fixed << setprecision(0) << rate << "/s"
        << flush;

   global_current_update_count_printed_once = false;
}
