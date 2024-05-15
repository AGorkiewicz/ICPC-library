bool operator<(const Vec &a, const Vec &b) {
    return make_pair(a.x, a.y) < make_pair(b.x, b.y);
}
struct Trapezoid {
    Vec bl, br, tl, tr;
};
T get_y(const ParamLine &l, T x) {
    return l.p.y + l.v.y * (x - l.p.x) / l.v.x;
}
struct CmpY {   
    T *x;   
    T y(const ParamLine &l) const {
        return get_y(l, *x);
    }
    bool operator()(const ParamLine &a, const ParamLine &b) const {
        return y(a) < y(b);
    }
};
vector<Trapezoid> trapezoidation(const vector<Vec> &poly) {
    const T leps = 1e-9;  
    int n = poly.size();
    auto previ = [&](int k) { return (k + n - 1) % n; };
    auto nexti = [&](int k) { return (k + 1) % n; };
    vector<int> pts(n);
    for(int i = 0; i < n; i++) pts[i] = i;
    sort(pts.begin(), pts.end(), [&](int a, int b) {
        return poly[a] < poly[b];
    });
    vector<bool> added(n);
    vector<Trapezoid> ans;
    T x; CmpY compare { &x };
    multimap<ParamLine, bool, CmpY> st(compare);
    for(int i: pts) {
        if(added[i]) continue;
        added[i] = true;
        x = poly[i].x;
        int i1 = i, i2 = i;
        int pi = previ(i1), ni = nexti(i2);
        while(sgn(poly[i1].x - poly[pi].x) == 0) {
            added[pi] = true;
            i1 = pi; pi = previ(pi);
        }
        while(sgn(poly[i2].x - poly[ni].x) == 0) {
            added[ni] = true;
            i2 = ni; ni = nexti(ni);
        }
        if(!added[pi] && !added[ni]) {
            if((i1 == i2 && prod(poly[pi] - poly[i], poly[ni] - poly[i]) < 0)
             || sgn(poly[i1].y - poly[i2].y) > 0) {
                swap(pi, ni); swap(i1, i2);
            }
            auto it1 = st.insert({ ParamLine(poly[i1], poly[pi]), true });
            auto it2 = st.insert({ ParamLine(poly[i2], poly[ni]), false });
            if(it1 != st.begin() && prev(it1)->second == true) {
                swap(it1->second, it2->second);
                auto &a = prev(it1)->first, &b = next(it2)->first;
                Vec na { x, compare.y(a) }, nb { x, compare.y(b) };
                ans.push_back({ a.p, na, b.p, nb });
                a.p = na; b.p = nb;
            }
        } else if(added[pi] && added[ni]) {
            if((i1 == i2 && prod(poly[pi] - poly[i], poly[ni] - poly[i]) > 0)
             || sgn(poly[i1].y - poly[i2].y) > 0) {
                swap(pi, ni); swap(i1, i2);  
            }
            auto it1 = st.lower_bound(ParamLine(poly[pi], poly[i1] - Vec { 0, leps }));
            auto it2 = prev(st.upper_bound(ParamLine(poly[ni], poly[i2] + Vec { 0, leps })));
            if(it1->second == true) {
                ans.push_back({ it1->first.p, poly[i1], it2->first.p, poly[i2] });
            } else {
                auto &a = prev(it1)->first, &b = next(it2)->first;
                Vec na { x, compare.y(a) }, nb { x, compare.y(b) };
                ans.push_back({ a.p, na, it1->first.p, poly[i1] });
                ans.push_back({ it2->first.p, poly[i2], b.p, nb });
                a.p = na; b.p = nb;           
            }
            st.erase(it1); st.erase(it2);
        } else {
            if(!added[pi]) {
                swap(pi, ni); swap(i1, i2);
            }
            auto it = st.lower_bound(ParamLine(poly[pi], poly[i1] - Vec { 0, leps }));
            assert(it != st.end());
            if(it->second) {
                auto &a = next(it)->first;
                Vec na { x, compare.y(a) };
                ans.push_back({ it->first.p, poly[i1], a.p, na });
                a.p = na;
            } else {
                auto &a = prev(it)->first;
                Vec na { x, compare.y(a) };
                ans.push_back({ a.p, na, it->first.p, poly[i1] });
                a.p = na;
            }
            it->first.p = poly[i2];
            it->first.v = poly[ni] - poly[i2];
        }
    }
    ans.erase(remove_if(ans.begin(), ans.end(), [](Trapezoid t) {
        return sgn(t.bl.x - t.br.x) == 0;
    }), ans.end());
    return ans;
}