#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;
struct chash { 
	const uint64_t C = ll(4e18 * acos(0)) | 71;
	ll operator()(ll x) const { return __builtin_bswap64((x^1234567891)*C); }
};// 1 << 16 is initial size, size has to be the power of 2
gp_hash_table<ll, int, chash> h({},{},{},{}, {1 << 16});
