#include <cassert>

using namespace std;

#define RD_1 rd()
#define RD_10 RD_1, RD_1, RD_1, RD_1, RD_1, RD_1, RD_1, RD_1, RD_1, RD_1
#define RD_100 RD_10, RD_10, RD_10, RD_10, RD_10, RD_10, RD_10, RD_10, RD_10, RD_10
#define MT_624_WORD_SEED RD_100, RD_100, RD_100, RD_100, RD_100, RD_100, RD_10, RD_10, RD_1, RD_1, RD_1, RD_1

// Reference used during implementation of this class:
// https://www.learncpp.com/cpp-tutorial/generating-random-numbers-using-mersenne-twister/
template<typename T>
prng_t<T>::prng_t()
{
   // The following is a standard-defined test that enures the random engine
   // is functioning correctly.
   constexpr T TEST_VALUE{
                            sizeof(T) == 4 ?
                            4123659995U :
                            (sizeof(T) == 8 ? 9981545732273789042ULL : 0ULL)
                         };

   if constexpr (TEST_VALUE != 0)
   {
      rand_eng.discard(9999);
      assert(rand_eng() == TEST_VALUE);
   }

   // Now re-seed the engine. Use of seed_seq to do this also ensures the
   // engine is sufficiently "warmed up" (meaning we don't need to explicitly
   // warm it up).
   //
   // We are providing 624 4-byte words of seed data to the engine. (The engine's
   // internal state size is 624 4-byte words.)
   //
   // Use of random_device may prove too slow on some platforms. If this occurs,
   // another technique will have to be used.
   random_device rd{};
   seed_seq ss{MT_624_WORD_SEED};
   rand_eng.seed(ss);
}

template<typename T>
prng_t<T>::~prng_t()
{
}

template<typename T>
T prng_t<T>::rand()
{
   return di(rand_eng);
}
