// Arithmetic mod 2^64-1. 2x slower than mod 2^64 and more
// code, but works on evil test data (e.g. Thue-Morse, where
// ABBA... and BAAB... of length 2^10 hash the same mod 2^64).
// "using H = ull;" instead if you think test data is random.
#define FOR(i, a, b) for (int i = (a); i < (b); i++)
using ull = uint64_t;
struct H {
	ull x; H(ull _x=0) : x(_x) {}
	H operator+(H o) { return x + o.x + (x + o.x < x); }
	H operator-(H o) { return *this + ~o.x; }
	H operator*(H o) { auto m = (__uint128_t)x * o.x;
		return H((ull)m) + (ull)(m >> 64); }
	ull get() const { return x + !~x; }
	bool operator==(H o) const { return get() == o.get(); }
	bool operator<(H o) const { return get() < o.get(); }
};
static const H C = (ll)1e11+3; // (order ~ 3e9; random also ok)
struct Hasher {
	vector<H> ha, pw;
	Hasher(string &str) : ha(SZ(str)+1), pw(ha) {
		pw[0] = 1;
		FOR(i,0,SZ(str)) {
			ha[i+1] = ha[i] * C + str[i];
			pw[i+1] = pw[i] * C;
		}
	}
	H hashInterval(int a, int b) { // hash [a, b]
		return ha[b + 1] - ha[a] * pw[b + 1 - a];
	}
};

H hashString(string& s){H h{}; for(char c:s) h=h*C+c;return h;}
