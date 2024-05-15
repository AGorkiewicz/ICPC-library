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
struct circle { point o; lf r; };
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
lf len(segment s){ return len(s.v); }
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
