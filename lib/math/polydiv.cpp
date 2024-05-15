vector <int> polydiv(vector <int> a, vector <int> b) {
	int n, m, i, k, s;
	n = a.size(); m = b.size();
	if (m > n) return {0};
	reverse(a.begin(), a.end());
	reverse(b.begin(), b.end());
	s = moddiv(1, b[0], MOD);
	for (int& x : b) x = modmul(x, s, MOD);
	k = n - m + 1;
	vector <int> r, v, g = {1};
	for (int w = 1; (1 << (w - 1)) < k; w++){
		r = polymul(g, g); r.resize(1 << w);
		v = b; v.resize(1 << w);
		r = polymul(r, v);
		r.resize(1 << w); g.resize(1 << w);
		polyadd(g, g); polysub(g, r);
	}
	g = polymul(g, a); g.resize(k);
	reverse(g.begin(), g.end());
	for (int& x : g) x = modmul(x, s, MOD);
	return g;
}