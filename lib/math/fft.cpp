typedef double T;
const T PI = acos(-1.0);
struct C {
    T re, im;
    C () {}
    C (T r) : re(r), im(0) {}
    C (T r, T i) : re(r), im(i) {}
    C operator * (const C &c) const {
        return C(re * c.re - im * c.im, im * c.re + re * c.im);
    }
    C operator + (const C &c) const {
        return C(re + c.re, im + c.im);
    }
    C operator - (const C &c) const {
        return C(re - c.re, im - c.im);
    }
    void operator += (const C &c) {
        re += c.re, im += c.im;
    }
    C conj() const {
        return C(re, -im);
    }
};
typedef vector < C > VC;
typedef vector < LL > VLL;
inline void FFT(C *a, int n, int dir) {
    for(int i = 0, j = 0; i < n; i++) {
        if(i > j) swap(a[i], a[j]);
        for(int k = n >> 1; (j ^= k) < k; k >>= 1);
    }
    for(int p = 2; p <= n; p <<= 1) {
        C wn(cos(2.0 * dir * PI / p), sin(2.0 * dir * PI / p));
        for(int k = 0; k < n; k += p) {
            C w = 1;
            for(int j = 0; j < (p >> 1); j++) {
                C xx = a[k + j];
                C yy = w * a[k + j + (p >> 1)];
                a[k + j] = xx + yy;
                a[k + j + (p >> 1)] = xx - yy;
                w = w * wn;
            }
        }
    }
}
void multiply(VLL &a, VLL &b, VLL &res)  {
    int n = max(a.size(), b.size()), p = 2;
    while((p >> 1) < n) p <<= 1;
    C *fa = new C[p + 4];
    for(int i = 0; i < p; i++) fa[i] = 0;
    for(int i = 0; i < sz(a); i++) fa[i] += C(a[i], 0);
    for(int i = 0; i < sz(b); i++) fa[i] += C(0, b[i]);
    FFT(fa, p, 1);
    for(int i = 0; i <= p / 2; i++) {
        C bp = fa[i] + fa[p - i == p ? 0 : p - i].conj();
        C _q = fa[p - i == p ? 0 : p - i] - fa[i].conj();
        C q(_q.im, _q.re);
        fa[i] = (bp * q) * C(0.25);
        if(i > 0) fa[p - i] = fa[i].conj();
    }
    FFT(fa, p, -1);
    res.resize(sz(a) + sz(b) - 1);
    for(int i = 0; i < sz(res); i++) {
        res[i] = round(fa[i].re / p);
    }
    delete [] fa;
}