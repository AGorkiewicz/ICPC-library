struct line { // f(x) = ax + b
	ll a, b; mutable ll p;
	bool operator<(const line& o) const { return a < o.a; }
	bool operator<(ll x) const { return p < x; }
};
struct lineContainer : multiset <line, less<>> {
	static const ll inf = LLONG_MAX; // for doubles inf = 1/0, div(a, b) = a / b
	ll div(ll a, ll b) { // floored division
		return a / b - ((a ^ b) < 0 && a % b);
	}
	bool isect(iterator x, iterator y) {
		if (y == end()) return x->p = inf, 0;
		if (x->a == y->a) x->p = x->b > y->b ? inf : -inf;
		else x->p = div(y->b - x->b, x->a - y->a);
		return x->p >= y->p;
	}
	void add(ll a, ll b) { // do NOT use insert
		auto z = insert({a, b, 0}), y = z++, x = y;
		while (isect(y, z)) z = erase(z);
		if (x != begin() && isect(--x, y)) isect(x, y = erase(y));
		while ((y = x) != begin() && (--x)->p >= y->p) isect(x, erase(y));
	}
	ll query(ll x) { // max value
		assert(!empty()); // or return -inf
		auto it = lower_bound(x);
		assert(it != end());
		return it->a * x + it->b;
	}
};
