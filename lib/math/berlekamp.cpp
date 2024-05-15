#define FOR(i, n) for(int i = 0; i < (n); i++)
#define sz(x) (int)(x).size()
const int N = 5005;
const int M = 1e9 + 7;
LL fast(LL a, LL n) {
    LL x = 1; a %= M;
    while(n) {
        if(n & 1) x = x * a % M;
        a = a * a % M; n >>= 1;
    }
    return x;
}
vector < LL > BM(vector < LL > x) {
    vector < LL > ls, cur;
    LL lf = 0, ld = 0;
    FOR(i, sz(x)) {
        LL t = 0;
        FOR(j, sz(cur)) t = (t + (LL)x[i - j - 1] * cur[j]) % M;
        if((t - x[i]) % M == 0) continue;
        if(cur.empty()) {
            cur.resize(i + 1);
            lf = i; ld = (t - x[i]) % M;
            continue;
        }
        LL k = -(x[i] - t) * fast(ld, M - 2) % M;
        vector < LL > c(i - lf - 1); c.push_back(k);
        for(auto y: ls) c.push_back(-y * k % M);
        if(sz(c) < sz(cur)) c.resize(sz(cur));
        FOR(j, sz(cur)) c[j] = (c[j] + cur[j]) % M;
        if(i - lf + sz(ls) >= sz(cur))
            ls = cur, lf = i, ld = (t - x[i]) % M;
        cur = c;
    }
    for(auto &y: cur) y = (y % M + M) % M;
    return cur;
}
int m;
LL a[N], h[N], t_[N], s[N], t[N];
void mull(LL *p, LL *q) {
    FOR(i, 2 * m) t_[i] = 0;
    FOR(i, m) if(p[i]) FOR(j, m)
        t_[i + j] = (t_[i + j] + p[i] * q[j]) % M;
    for(int i = 2 * m - 1; i >= m; i--) if(t_[i])
        for(int j = m - 1; ~j; --j)
            t_[i - j - 1] = (t_[i - j - 1] + t_[i] * h[j]) % M;
    FOR(i, m) p[i] = t_[i];
}
LL calc(LL k) {
    for(int i = m; ~i; i--) s[i] = t[i] = 0;
    s[0] = 1; (m != 1 ? t[1] = 1 : t[0] = h[0]);
    while(k) {
        if(k & 1) mull(s, t);
        mull(t, t); k >>= 1;
    }
    LL su = 0;
    FOR(i, m) su = (su + s[i] * a[i]) % M;
    return (su % M + M) % M;
}
LL nth_element(vector < LL > x, LL n) {
    if(n < (int)sz(x)) return x[n];
    vector < LL > v = BM(x); m = v.size(); if(!m) return 0;
    FOR(i, m) h[i] = v[i], a[i] = x[i];
    return calc(n);
}