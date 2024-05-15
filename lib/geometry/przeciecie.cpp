#define ALL(X) X.begin(), X.end()
#define FORW(I, A, B) for (int(I) = (A); (I) < (B); (I)++)
#define SIZE(X) int(X.size())
#define PB push_back
inline int type(const Vec &p) {
    return sgn(p.y) == 1 or (sgn(p.y) == 0 && sgn(p.x) == 1);
}
bool compare_angle(const Vec &a, const Vec &b) {
    int at = type(a), bt = type(b);
    if (at != bt)
        return at < bt;
    int p = sgn(prod(a, b));
    if(p) return p > 0;
    return sgn(len2(a) - len2(b)) == -1;
}
bool operator<(const ParamLine &a, const ParamLine &l) {
    if (sgn(a.v.x - l.v.x) or sgn(a.v.y - l.v.y))
        return compare_angle(
            a.v, l.v);
    return sgn(prod(a.v, l.p - a.p)) < 0;
}
int sgn_dist(const ParamLine &l, const Vec &u) {
    return sgn(prod(l.v, u - l.p));
}
vector<Vec> halfcoat(vector<ParamLine> h) {
    const static int MAXN = 40020;
    static const T Z = 1e6;
    static Vec p[MAXN];
    static Vec box[4] = {
        { Z, -Z },
        { Z, Z },
        { -Z, Z },
        { -Z, -Z }};
    FORW(i, 0, 4)
    h.PB(ParamLine(box[i], box[(i + 1) % 4], true));
    int n = SIZE(h), z = 0;
    sort(ALL(h));
    FORW(i, 0, n)
    if (i == 0 or (sgn(h[i].v.x - h[i - 1].v.x) or sgn(h[i].v.y - h[i - 1].v.y)))
        h[z++] = h[i];
    n = z;
    int m = 0, del = 0;
    FORW(i, 1, n)
    {
        while (m > del and sgn_dist(h[i], p[m - 1]) <= 0)
            --m;
        while (m > del and sgn_dist(h[i], p[del]) <= 0)
            ++del;
        if (del == m and sgn(prod(h[m].v, h[i].v)) <= 0)
            return {};
        Vec q = intersection(h[i], h[m]);
        if (sgn_dist(h[del], q) >= 0)
            p[m++] = q, h[m] = h[i];
    }
    rotate(p, p + del, p + m);
    rotate(h.begin(), h.begin() + del, h.end());
    m -= del;
    if (m == 0)
        return {};
    Vec q = intersection(h[0], h[m]);
    p[m++] = q;
    return vector<Vec>(p, p + m);
}