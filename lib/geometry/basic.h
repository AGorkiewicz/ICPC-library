typedef long double T;
int sgn(T x) {
    const T eps = 1e-9;
    if(abs(x) <= eps) return 0;
    return x > 0 ? 1 : -1;
}
struct Vec {
    T x, y;
};
Vec operator+(const Vec &a, const Vec &b) {
    return { a.x + b.x, a.y + b.y }; 
}
Vec operator-(const Vec &a, const Vec &b) {
    return { a.x - b.x, a.y - b.y };
}
Vec operator*(const Vec &a, const T &b) {
    return  { a.x * b, a.y * b };
}
Vec operator/(const Vec &a, const T &b) {
    return  { a.x / b, a.y / b };
}
T dot(const Vec &a, const Vec &b) {
    return a.x * b.x + a.y * b.y;
}
T prod(const Vec &a, const Vec &b) {
    return a.x * b.y - a.y * b.x;
}
T len(const Vec &v) {
    return sqrt(dot(v, v));
}
T len2(const Vec &v) {
    return dot(v, v);
}
T alpha(const Vec &v) {
    return atan2(v.y, v.x);
}
struct ParamLine {
    Vec p, v;
    ParamLine() = default;
    ParamLine(Vec a, Vec b, bool norm=false) {
        p = a; v = b - a;
        if(norm) v = v / len(v);
    }
};
Vec project(const ParamLine &l, const Vec &u) {
    return l.p + l.v * dot((u - l.p), l.v) / len2(l.v);
}
T dist(const ParamLine &l, const Vec &u) {
    return abs(prod(l.v, u - l.p) / len(l.v));
}
Vec intersection(ParamLine a, ParamLine b) {
	T norm = prod(a.v, b.v);
	T t = prod((b.p - a.p), b.v) / norm;
	return a.p + a.v * t;
}