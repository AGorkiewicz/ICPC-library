typedef long double T;
struct Vec { T x, y; };
inline Vec operator+(const Vec &a, const Vec &b) {
    return { a.x + b.x, a.y + b.y }; 
}
inline Vec operator-(const Vec &a, const Vec &b) {
    return { a.x - b.x, a.y - b.y };
}
inline Vec operator*(const Vec &a, const T &b) {
    return  { a.x * b, a.y * b };
}
inline Vec operator/(const Vec &a, const T &b) {
    return  { a.x / b, a.y / b };
}
inline T dot(const Vec &a, const Vec &b) {
    return a.x * b.x + a.y * b.y;
}
inline T prod(const Vec &a, const Vec &b) {
    return a.x * b.y - a.y * b.x;
}
inline T len(const Vec &v) {
    return sqrt(dot(v, v));
}
inline T len2(const Vec &v) {
    return dot(v, v);
}
inline T alpha(const Vec &v) {
    return atan2(v.y, v.x);
}
struct ParamLine {
    Vec p, v;
    ParamLine() = default;
    ParamLine(Vec a, Vec b) {
        p = a;
        v = b - a;
    }
};
Vec project(const ParamLine &l, const Vec &u) {
    return l.p + l.v * dot((u - l.p), l.v) / len2(l.v);
}
T dist(const ParamLine &l, const Vec &u) {
    return abs(prod(l.v, u - l.p) / len(l.v));
}
struct Line {
    T A, B, C;
    Line() = default;
    Line(Vec a, Vec b)  {
        Vec d = b - a;
        A = -d.y; B = d.x;
        C = -(A * a.x + B * a.y);
    }
    Line(ParamLine l) {
        A = -l.v.y; B = l.v.x;
        C = -(A * l.p.x + B * l.p.y);
    }
};
Vec intersect(const Line &a, const Line &b) {
    T norm = a.B * b.A - a.A * b.B;
    return Vec { a.B * b.C - a.C * b.B, a.C * b.A - a.A * b.C } / -norm;
}
T dist(const Line &l, const Vec &v) {
    return abs(l.A * v.x + l.B * v.y + l.C) / sqrt(l.A * l.A + l.B * l.B);
}
struct Circle {
    Vec o; T r;
};
pair<Vec, Vec> intersect(const Circle &a, const Circle &b) {
    Vec v = b.o - a.o; T d = len(v);
    T x = (d * d + a.r * a.r - b.r * b.r) / (2 * d);
    T y = sqrt(a.r * a.r - x * x);
    v = v / d; Vec u { -v.y, v.x };
    return { a.o + v * x + u * y, a.o + v * x - u * y };
}
pair<Vec, Vec> intersect(const Circle &c, const ParamLine &l) {
    Vec pr = project(l, c.o);
    T t = sqrt(c.r * c.r - len2(pr - c.o));
    Vec v = l.v / len(l.v);
    return { pr + v * t, pr - v * t };
}
pair<Vec, Vec> tangent(const Circle &c, const Vec &v) {
    Vec d = v - c.o;
    T r = sqrt(len2(d) - c.r * c.r);
    return intersect(c, Circle { v, r } );
}
typedef ParamLine Segment;
T len(const Segment &s) {
    return len(s.v);
}
bool on_segment(const Segment &s, Vec p) {
    p = p - s.p;
    const T eps = 1e-9;
    auto d = dot(s.v, p);
    return -eps <= d && d <= dot(s.v, s.v) + eps && prod(s.v, p) < eps;
}
T segment_dist(const Segment &s, const Vec &v) {
    Vec p = project(s, v);
    if(on_segment(s, p))
        return len(v - p);
    return min(len(s.p - v), len(s.p + s.v - v));
}
bool segment_intersect(const Segment &a, const Segment &b) {
    const T eps = 1e-9; //zmienic na ujemna wartosc dla przecinania bez koncow
    return prod(b.p - a.p, a.v) * prod(b.p + b.v - a.p, a.v) < eps &&
        prod(a.p - b.p, b.v) * prod(a.p + a.v - b.p, b.v) < eps;
}
void test_lines(Vec a, Vec b, Vec c, Vec d) {
    Line l1(a, b), l2(c, d);
    const T eps = 1e-6;
    assert(dist(l1, a) < eps && dist(l1, b) < eps && dist(l2, c) < eps && dist(l2, d) < eps);
    auto in = intersect(l1, l2);
    assert(dist(l1, in) < eps && dist(l2, in) < eps);
    ParamLine pl1(a, b), pl2(c, d);
    assert(dist(pl1, a) < eps && dist(pl1, b) < eps && dist(pl2, c) < eps && dist(pl2, d) < eps);
    in = intersect(Line(l1), Line(l2));
    assert(dist(pl1, in) < eps && dist(pl2, in) < eps);
}
void test_circles(Vec o1, Vec o2, T r1, T r2) {
    assert(len(o1 - o2) <= r1 + r2);
    if(len(o1 - o2) < abs(r1 - r2))
        return;
    const T eps = 1e-6;
    Circle c1 { o1, r1 }, c2 { o2, r2 };
    auto in = intersect(c1, c2);
    for(auto x: { in.first, in.second }) {
        //printf("%.15Lf %.15Lf\n", r1 - len(o1 - x), r2 - len(o2 - x));
        assert(abs(r1 - len(o1 - x)) < eps && abs(r2 - len(o2 - x) < eps));
    }
}
void test_circle_line(Vec o, T r, Vec a, Vec b) {
    Circle c { o, r }; ParamLine l(a, b);
    auto in = intersect(c, l);
    const T eps = 1e-6;
    for(auto x: { in.first, in.second })
        assert(abs(r - len(o - x)) < eps && abs(dist(l, x)) < eps);
    c.r = (0.5 + rand()) / (RAND_MAX + 1.0) * len(o - a);
    auto t = tangent(c, a);
    for(auto x: { t.first, t.second }) {
        //cout << abs(c.r - len(x - o)) << " " << abs(dot(x - a, x - o)) << endl;
        assert(abs(c.r - len(x - o)) < eps && abs(dot(x - a, x - o) / len(x - a) / len(x - o) < eps));
    }
}
int main() {
    for(int i = 0; i < 10000; i++) {
        Vec v[4];
        for(auto &x: v)
            x = { rand(), rand() };
        test_lines(v[0], v[1], v[2], v[3]);
    }
    for(int i = 0; i < 10000; i++) {
        Vec v[2];
        for(auto &x: v)
            x = { rand(), rand() };
        T r1 = rand(), r2 = rand() + max(T(), len(v[0] - v[1]) - r1);
        test_circles(v[0], v[1], r1, r2);
    }
    for(int i = 0; i < 10000; i++) {
        Vec v[3];
        for(auto &x: v)
            x = { rand(), rand() };
        T r = rand() + dist(ParamLine(v[1], v[2]), v[0]);
        test_circle_line(v[0], r, v[1], v[2]);
    }
}


