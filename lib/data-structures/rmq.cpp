// uzycie - RMQ < int, max > R(n, t);
template < typename TP, const TP& (*F)(const TP&, const TP&) >
struct RMQ {
	int n; vector < TP > t;
	vector < vector < TP > > res;
	RMQ(vector < TP > T) : n(sz(T)), t(T) {
		res.push_back(t);
		for(int p = 2; p <= n; p <<= 1) {
			vector < TP > tmp(n - p + 1);
			for(int j = 0; j <= n - p; j++)
				tmp[j] = F(res.back()[j], res.back()[j + p / 2]);
			res.push_back(tmp);
		}
	}
	TP query(int a, int b) {
		int d = b - a + 1, lg = __lg(d);
		return F(res[lg][a], res[lg][b - (1 << lg) + 1]);
	}
};
