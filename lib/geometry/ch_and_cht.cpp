point rot90(point a) { return point(-a.y, a.x); }
vector <point> convex_hull(vector <point> points, bool strict){
	sort(all(points));
	vector <point> hull;
	rep(phase, 0, 1){
		int start = ss(hull);
		for (point p : points){
			while (hull.size() >= start + 2){
				ll iw = IW(p, hull.back(), hull[ss(hull) - 2]);
				if (iw < 0 || iw == 0 && strict == false) break;
				hull.pop_back();
			}
			hull.pb(p);
		}
		hull.pop_back();
		reverse(all(points));
	}
	if (ss(hull) == 2 && hull[0] == hull[1]){
		hull.pop_back();
	}
	return hull;
}
struct cht {
	vector <point> hull, vecs;
	void insert(point p) // maintains lower hull. p.x should increase
	{
		while (!vecs.empty() && dot(vecs.back(), p - hull.back()) <= 0)
		{
			hull.pop_back();
			vecs.pop_back();
		}
		if (!hull.empty()){
			vecs.pb(rot90(p - hull.back()));
		}
		hull.pb(p);
	}
	ll query(point p) // minimum dot product
	{
		auto it = lower_bound(all(vecs), p, [] (point a, point b) {
			return cross(a, b) > 0;
		});
		return dot(p, hull[it - vecs.begin()]);
	}
};
