#include <mutex>
#include <limits>

using namespace std;

#include "fundamental_types.h"
#include "globals.h"
#include "prng.h"
#include "update_screen.h"

#include "thread_main.h"

void thread_main()
{
   my_uint_t min_n{numeric_limits<my_uint_t>::max()};
   my_uint_t max_n{0};
   prng_t<my_uint_t> prng;

   while (true)
   {
      my_uint_t i_last_update{0};

      for (my_uint_t i{1}; i <= GLOBAL_COUNT_FULL_UPDATE_PERIOD; ++i)
      {
         bool thread_update_made{false};

         my_uint_t one_num{prng.rand()};

         if (one_num > max_n)
         {
            max_n = one_num;
            thread_update_made = true;
         }

         if (one_num < min_n)
         {
            min_n = one_num;
            thread_update_made = true;
         }

         if (thread_update_made)
         {
            lock_guard<recursive_mutex> lg_global_max_min_update_count_mutex{
                                                  global_max_min_update_count_mutex
                                                                            };
            lock_guard<recursive_mutex> lg_global_total_count_mutex{
                                                  global_total_count_mutex
                                                                   };
            bool screen_update_needed{false};

            if (one_num > global_max_n)
            {
               global_max_n = one_num;
               screen_update_needed = true;
            }

            if (one_num < global_min_n)
            {
               global_min_n = one_num;
               screen_update_needed = true;
            }

            if (screen_update_needed)
            {
               ++global_update_count;
               global_total_count += (i - i_last_update);
               i_last_update = i;
               update_screen();
               global_current_update_count_printed_once = true;
            }
         }
      }

      {
         lock_guard<recursive_mutex> lg{global_total_count_mutex};
         global_total_count += (GLOBAL_COUNT_FULL_UPDATE_PERIOD - i_last_update);

         if (global_total_count % SCREEN_UPDATE_PERIOD == 0)
            update_screen();
      }
   }
}
