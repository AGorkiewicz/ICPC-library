/* Prec. error max_ans/1e15 (2.5e18) for (long) doubles, so int rounding works
for doubles with answers 0.5e15, e.g. for sizes 2^20 and RANDOM ints in [0,45k],
assuming DBL_MANT_DIG=53 and LDBL_MANT_DIG=64. Consider normalizing and brute.*/
#define REP(i,n) for(int i = 0; i < int(n); ++i)
typedef double ld; // 'long double' is 2.2 times slower
struct C { ld re, im;
	C operator * (const C & he) const {
		return C{re * he.re - im * he.im,
				re * he.im + im * he.re};
	}
	void operator += (const C & he) { re += he.re; im += he.im; }
};
void dft(vector<C> & a, bool rev) {
	const int n = a.size();
	for(int i = 1, k = 0; i < n; ++i) {
		for(int bit = n / 2; (k ^= bit) < bit; bit /= 2);;;
		if(i < k) swap(a[i], a[k]);
	}
	for(int len = 1, who = 0; len < n; len *= 2, ++who) {
		static vector<C> t[30];
		vector<C> & om = t[who];
		if(om.empty()) {
			om.resize(len);
			const ld ang = 2 * acosl(0) / len;
			REP(i, len) om[i] = i%2 || !who ?
					C{cos(i*ang), sin(i*ang)} : t[who-1][i/2];
		}
		for(int i = 0; i < n; i += 2 * len)
			REP(k, len) {
				 const C x = a[i+k], y = a[i+k+len]
						* C{om[k].re, om[k].im * (rev ? -1 : 1)};
				a[i+k] += y;
				a[i+k+len] = C{x.re - y.re, x.im - y.im};
			}
	}
	if(rev) REP(i, n) a[i].re /= n;
} 
template<typename T>vector<T> multiply(const vector<T> & a, const vector<T> & b,
		bool split = true, bool normalize = false) {
	if(a.empty() || b.empty()) return {};
	T big = 0; if(normalize) { // [0,B] into [-B/2, B/2]
		assert(a.size() == b.size()); // equal size!!!
		for(T x : a) big = max(big, x);
		for(T x : b) big = max(big, x);
		big /= 2;
	}
	int n = a.size() + b.size();
	vector<T> ans(n - 1);
	/* if(min(a.size(),b.size()) < 190) { // BRUTE FORCE
		REP(i, a.size()) REP(j, b.size()) ans[i+j] += a[i]*b[j];
		return ans; } */
	while(n&(n-1)) ++n;
	auto foo = [&](const vector<C> & w, int i, int k) {
		int j = i ? n - i : 0, r = k ? -1 : 1;
		return C{w[i].re + w[j].re * r, w[i].im
				- w[j].im * r} * (k ? C{0, -0.5} : C{0.5, 0});
	};
	if(!split) { // standard fast version
		vector<C> in(n), done(n);
		REP(i, a.size()) in[i].re = a[i] - big;
		REP(i, b.size()) in[i].im = b[i] - big;
		dft(in, false);
		REP(i, n) done[i] = foo(in, i, 0) * foo(in, i, 1);
		dft(done, true);
		REP(i, ans.size()) ans[i] = is_integral<T>::value ?
				llround(done[i].re) : done[i].re;
	//REP(i,ans.size())err=max(err,abs(done[i].re-ans[i]));
	}
	else { // Split big INTEGERS into pairs a1*M+a2,
		const T M = 1<<15; // where M = sqrt(max_absvalue).
		vector<C> t[2]; // This version is 2.2-2.5 times slower.
		REP(x, 2) {
			t[x].resize(n);
			auto & in = x ? b : a; // below use (in[i]-big) if normalized
			REP(i, in.size()) t[x][i]=C{ld(in[i]%M), ld(in[i]/M)};
			dft(t[x], false);
		}
		T mul = 1;
		for(int s = 0; s < 3; ++s, mul = (mul*M)%mod) {
			vector<C> prod(n);
			REP(x, 2) REP(y, 2) if(x + y == s) REP(i, n)
				prod[i] += foo(t[0], i, x) * foo(t[1], i, y);
			dft(prod, true); // remember: llround(prod[i].re)%MOD*mul !!!
			REP(i, ans.size()) ans[i]= (ans[i]+llround(prod[i].re)%mod*mul)%mod;
		}
	}
	if(normalize) {
		T so_far = 0;
		REP(i, ans.size()) {
			if(i < (int) a.size()) so_far += a[i] + b[i];
			else so_far -= a[i-a.size()] + b[i-a.size()];
			ans[i] += big * so_far - big * big * min(i + 1, (int) ans.size() - i);
		}
	}
	return ans;
}
