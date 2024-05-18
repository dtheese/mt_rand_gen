#ifndef FUNDAMENTAL_TYPES_INCLUDED
#define FUNDAMENTAL_TYPES_INCLUDED

#include <cstdint>
#include <type_traits>

using namespace std;

using my_uint_t = uint64_t;

static_assert(
                sizeof(my_uint_t) == 8 &&
                is_integral_v<my_uint_t> &&
                is_unsigned_v<my_uint_t>,
                "my_uint_t must be a 64-bit unsigned integer type"
             );

#endif
