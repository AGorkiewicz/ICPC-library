bool operator<(const Vec &a, const Vec &b) {
    return make_pair(a.x, a.y) < make_pair(b.x, b.y);
} //first element - min lex, other sorted clockwise
vector<Vec> convexHull(vector<Vec> points) {
    auto it = min_element(points.begin(), points.end());
    auto o = *it; points.erase(it);
    sort(points.begin(), points.end(), [o](Vec a, Vec b) {
        int s = sgn(prod(a - o, b - o));
        return s < 0 || (s == 0 && len2(a) < len2(b));
    });
    vector<Vec> ans { o };
    for(auto p: points) {
        while(ans.size() > 1) {
            auto a = ans[ans.size()-2], b = ans[ans.size()-1];
            if(sgn(prod(p - a, b - a)) > 0) break;
            ans.pop_back();
        }
        ans.push_back(p);
    }
    return ans;
} //zwraca czy v jest scisle wewnatrz otoczki (bez brzegow)
bool insideHull(const vector<Vec> &hull, const Vec &v) {
    auto o = hull[0];
    if(v < o || sgn(prod(hull[1] - o, v - o)) == 0 || sgn(prod(hull.back() - o, v - o)) == 0) return false;
    auto it = lower_bound(hull.begin() + 1, hull.end(), v, [o](Vec a, Vec b) {
        return prod(a - o, b - o) < 0;
    });
    if(it == hull.begin() + 1 || it == hull.end()) return false;
    return prod(v - *it, *prev(it) - *it) < 0;
}