#include <bits/stdc++.h>
using namespace std;

using lf = long double;
using point = pair <lf, lf>;
#define x first
#define y second

point operator+(point a, point b) { return {a.x + b.x, a.y + b.y}; }
point operator-(point a, point b) { return {a.x - b.x, a.y - b.y}; }
point operator*(lf a, point b) { return {a * b.x, a * b.y}; }
point operator/(point a, lf b) { return {a.x / b, a.y / b}; }
lf cross(point a, point b) { return a.x * b.y - a.y * b.x; }
lf dot(point a, point b) { return a.x * b.x + a.y * b.y; }
lf len2(point v) { return dot(v, v); }
lf len(point v) { return sqrt(len2(v)); }
struct paramline {
    point p, v;
    paramline() = default;
    paramline(point a, point b) : p(a), v(b - a) {}
};
point project(paramline l, point u){
    return l.p + dot((u - l.p), l.v) * l.v / len2(l.v);
}
lf dist(paramline l, point u){
    return abs(cross(l.v, u - l.p) / len(l.v));
}
struct line {
    lf A, B, C;
    line() = default;
    line(point a, point b){
        point d = b - a;
        A = -d.y;
		B = d.x;
        C = -(A * a.x + B * a.y);
    }
    line(paramline l){
        A = -l.v.y;
		B = l.v.x;
        C = -(A * l.p.x + B * l.p.y);
    }
};
point intersect(line a, line b){
    lf norm = a.B * b.A - a.A * b.B;
    return point{a.B * b.C - a.C * b.B, a.C * b.A - a.A * b.C} / -norm;
}
lf dist(line l, point v){
    return abs(l.A * v.x + l.B * v.y + l.C) / sqrt(l.A * l.A + l.B * l.B);
}
struct circle {
	point o;
	lf r;
};
pair <point, point> intersect(circle a, circle b){
    point v = b.o - a.o;
	lf d = len(v);
    lf x = (d * d + a.r * a.r - b.r * b.r) / (2 * d);
    lf y = sqrt(a.r * a.r - x * x);
    v = v / d;
	point u{-v.y, v.x};
    return {a.o + x * v + y * u, a.o + x * v - y * u};
}
pair <point, point> intersect(circle c, paramline l){
    point pr = project(l, c.o);
    lf t = sqrt(c.r * c.r - len2(pr - c.o));
    point v = l.v / len(l.v);
    return {pr + t * v, pr - t * v};
}
pair <point, point> tangent(circle c, point v){
    point d = v - c.o;
    lf r = sqrt(len2(d) - c.r * c.r);
    return intersect(c, circle{v, r});
}
using segment = paramline;
lf len(segment s){
    return len(s.v);
}
bool on_segment(segment s, point p){
    p = p - s.p;
    const lf eps = 1e-9, d = dot(s.v, p);
    return -eps <= d && d <= dot(s.v, s.v) + eps && cross(s.v, p) < eps;
}
lf segment_dist(segment s, point v){
    point p = project(s, v);
    if (on_segment(s, p)) return len(v - p);
    return min(len(s.p - v), len(s.p + s.v - v));
}
bool segment_intersect(segment a, segment b){
    const lf eps = 1e-9; // change to negative to exclude endpoints
    return cross(b.p - a.p, a.v) * cross(b.p + b.v - a.p, a.v) < eps && 
		cross(a.p - b.p, b.v) * cross(a.p + a.v - b.p, b.v) < eps;
}
void test_lines(point a, point b, point c, point d){
    line l1(a, b), l2(c, d);
    const lf eps = 1e-6;
    assert(dist(l1, a) < eps && dist(l1, b) < eps && dist(l2, c) < eps && dist(l2, d) < eps);
    auto in = intersect(l1, l2);
    assert(dist(l1, in) < eps && dist(l2, in) < eps);
    paramline pl1(a, b), pl2(c, d);
    assert(dist(pl1, a) < eps && dist(pl1, b) < eps && dist(pl2, c) < eps && dist(pl2, d) < eps);
    in = intersect(line(l1), line(l2));
    assert(dist(pl1, in) < eps && dist(pl2, in) < eps);
}
void test_circles(point o1, point o2, lf r1, lf r2) {
    assert(len(o1 - o2) <= r1 + r2);
    if (len(o1 - o2) < abs(r1 - r2)) return;
    const lf eps = 1e-6;
    circle c1 { o1, r1 }, c2 { o2, r2 };
    auto in = intersect(c1, c2);
    for(auto x: { in.first, in.second }) {
        //printf("%.15Lf %.15Lf\n", r1 - len(o1 - x), r2 - len(o2 - x));
        assert(abs(r1 - len(o1 - x)) < eps && abs(r2 - len(o2 - x) < eps));
    }
}
void test_circle_line(point o, lf r, point a, point b) {
    circle c { o, r }; paramline l(a, b);
    auto in = intersect(c, l);
    const lf eps = 1e-6;
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
        point v[4];
        for(auto &x: v)
            x = { rand(), rand() };
        test_lines(v[0], v[1], v[2], v[3]);
    }
    for(int i = 0; i < 10000; i++) {
        point v[2];
        for(auto &x: v)
            x = { rand(), rand() };
        lf r1 = rand(), r2 = rand() + max(lf(), len(v[0] - v[1]) - r1);
        test_circles(v[0], v[1], r1, r2);
    }
    for(int i = 0; i < 10000; i++) {
        point v[3];
        for(auto &x: v)
            x = { rand(), rand() };
        lf r = rand() + dist(paramline(v[1], v[2]), v[0]);
        test_circle_line(v[0], r, v[1], v[2]);
    }
}
