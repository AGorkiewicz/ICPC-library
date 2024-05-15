/* returns O(n) edges which contains MST in O(nlogn) */
using P = Point<int>;
vector<array<int, 3>> manhattanMST(vector<P> ps) {
	vi id(SZ(ps));
	iota(all(id), 0);
	vector<array<int, 3>> edges;
	FOR(k,0,4) {
		sort(all(id), [&](int i, int j) {
		     return (ps[i]-ps[j]).x < (ps[j]-ps[i]).y;});
		map<int, int> sweep;
		for (int i : id) {
			for (auto it = sweep.lower_bound(-ps[i].y);
				        it != sweep.end(); sweep.erase(it++)) {
				int j = it->second;
				P d = ps[i] - ps[j];
				if (d.y > d.x) break;
				edges.pb({d.y + d.x, i, j});
			}
			sweep[-ps[i].y] = i;
		}
		for (P& p : ps) if (k & 1) p.x = -p.x; else swap(p.x, p.y);
	}
	return edges;
}
