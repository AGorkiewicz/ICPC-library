const double EPS = 1e-7; 
typedef long double T; 
typedef vector <T> VT;
typedef vector < int > vi;
#define FOR(i,n) for(int i = 0; i < (n); i++)
vector < VT > A; VT b, c, res; vi kt, N; int m;
inline void pivot(int k, int l, int e) {
	int x = kt[l]; T p = A[l][e];
	FOR(i, k) A[l][i] /= p; b[l] /= p; N[e] = 0;
	FOR(i, m) if(i != l) b[i] -= A[i][e] * b[l], A[i][x] = A[i][e] * -A[l][x];
	FOR(j, k) if(N[j]) {
		c[j] -= c[e] * A[l][j];
		FOR(i, m) if(i != l) A[i][j] -= A[i][e] * A[l][j];
	}
	kt[l] = e; N[x] = 1; c[x] = c[e] * -A[l][x];
}
VT doit(int k) {
	VT res; T best;
	while(1) {
		int e = -1, l = -1; FOR(i, k) if(N[i] && c[i] > EPS) {e = i; break;}
		if(e == -1) break;
		FOR(i, m) if(A[i][e] > EPS && (l == -1 || best > b[i] / A[i][e]))
			best = b[ l = i ]  / A[i][e];
		if(l == -1)
			return VT();
		pivot(k, l, e);
	}
	res.resize(k, 0); FOR(i, m) res[kt[i]] = b[i];
	return res;
} /* AA * x <= bb, max cc * x */
VT simplex(const vector < VT > &AA, const VT &bb, const VT &cc) {
	int n = AA[0].size(), k;
	m = AA.size(); k = n + m + 1; kt.resize(m); b = bb; c = cc; c.resize(n + m);
	A = AA; FOR(i, m) { A[i].resize(k); A[i][n + i] = 1; A[i][k - 1] = -1; kt[i] = n + i; }
	N = vi(k, 1); FOR(i, m) N[kt[i]] = 0;
	int pos = min_element(b.begin(), b.end()) - b.begin();
	if(b[pos] < -EPS) {
		c = VT(k, 0); c[k - 1] = -1; pivot(k, pos, k - 1); res = doit(k);
		if(res[k - 1] > EPS) return VT();
		FOR(i, m) if (kt[i] == k - 1) {
			FOR(j, k - 1) if(N[j] && (A[i][j] < -EPS || EPS < A[i][j])) {
				pivot(k, i, j); break;
			}
		}
		c = cc; c.resize(k, 0); FOR(i, m) FOR(j, k) if(N[j]) c[j] -= c[kt[i]] * A[i][j];
	}
	res = doit(k - 1); if(!res.empty()) res.resize(n);
	return res;
}