/* p_f:the prefix sum of f(x) (1 <= x <= th).
p_g:the prefix sum of g(x) (0 <= x <= N).
p_c:the prefix sum of (f * g)(x) (0 <= x <= N). */
struct prefix_mul { /* th - threshold ~ N^2/3 */
 	typedef ll (*func) (ll);
	func p_f, p_g, p_c; ll n, th, inv;
	unordered_map <ll,ll> mem;
	prefix_mul(func p_f, func p_g, func p_c) : p_f(p_f), p_g(p_g), p_c(p_c) {}
	ll calc(ll x) {
		if (x <= th) return p_f(x);
		auto d = mem.find(x);
		if (d != mem.end()) return d->second;
		ll ans = 0;
		for (ll i = 2, la; i <= x; i = la + 1){
			la = x / (x / i);
			ans = ans + (p_g(la) - p_g(i - 1)) * calc(x / i);
		}
		ans = (p_c(x) - ans) / inv;
		return mem[x] = ans;
	}
	ll solve(ll n, ll th) {
		if (n <= 0) return 0;
		prefix_mul::n = n; prefix_mul::th = th;
		inv = p_g(1); return calc(n); 
	}
};