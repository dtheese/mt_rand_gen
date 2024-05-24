#include <future>
#include <vector>

using namespace std;

#include "globals.h"
#include "thread_main.h"

int main()
{
   vector<future<void>> futures;

   for (size_t i{0}; i < NUM_THREADS; ++i)
      futures.push_back(async(launch::async, thread_main));

   // TODO: All threads run forever, so this has the effect of permanently suspending
   // TODO: the main thread. There's probably a better way to do this...
   for (size_t i{0}; i < NUM_THREADS; ++i)
      futures[i].get();
}
