#include <future>
#include <vector>

using namespace std;

#include "globals.h"
#include "thread_main.h"
#include "update_screen.h"

int main()
{
   update_screen();
   global_current_update_count_printed_once = true;

   vector<future<void>> futures;

   for (size_t i{0}; i < NUM_THREADS; ++i)
      futures.push_back(async(launch::async, thread_main));

   // All threads run forever, so this has the effect of permanently suspending
   // the main thread.
   for (size_t i{0}; i < NUM_THREADS; ++i)
      futures[i].get();
}
