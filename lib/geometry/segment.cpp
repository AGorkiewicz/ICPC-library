typedef ParamLine Segment;
T len(const Segment &s) {
    return len(s.v);
}
bool on_segment(const Segment &s, Vec p) {
    p = p - s.p; const T eps = 1e-9;
    auto d = dot(s.v, p);
    return -eps <= d && d <= dot(s.v, s.v) + eps && prod(s.v, p) < eps;
}
T segment_dist(const Segment &s, const Vec &v) {
    Vec p = project(s, v);
    if(on_segment(s, p)) return len(v - p);
    return min(len(s.p - v), len(s.p + s.v - v));
}
bool intersect(const Segment &a, const Segment &b) {
    if(sgn(prod(a.v, b.v)) == 0) {
        if(sgn(prod(a.p - b.p, a.v)) != 0) return false;
        auto s1 = dot(a.v, a.p), t1 = dot(a.v, a.p + a.v), s2 = dot(a.v, b.p), t2 = dot(a.v, b.p + b.v);
        if(s2 < t2) swap(s2, t2);
        return max(s1, s2) <= min(t1, t2);
    }
    return sgn(prod(b.p - a.p, a.v)) * sgn(prod(b.p + b.v - a.p, a.v)) <= 0 &&
        sgn(prod(a.p - b.p, b.v)) * sgn(prod(a.p + a.v - b.p, b.v)) <= 0;
}