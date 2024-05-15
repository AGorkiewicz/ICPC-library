struct Circle {
    Vec o;
    T r;
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
void tangents(Vec c, double r1, double r2, vector<ParamLine> & ans) {
    double r = r2 - r1;
    double z = c.x * c.x + c.y * c.y;
    double d = z - r * r;
    if(sgn(d) == -1)  return;
    d = sqrt (abs (d));
    Vec v { c.x * d - c.y * r, c.x * r + c.y * d };
    Vec p = Vec { -v.y, v.x } * r1 / z;
    ans.emplace_back(p, p + v);
}
vector<ParamLine> tangents (Circle a, Circle b) {
    vector<ParamLine> ans;
    for (int i=-1; i<=1; i+=2)
        for (int j=-1; j<=1; j+=2)
            tangents (b.o-a.o, a.r*i, b.r*j, ans);
    for (size_t i=0; i<ans.size(); ++i)
        ans[i].p = ans[i].p + a.o;
    return ans;
}