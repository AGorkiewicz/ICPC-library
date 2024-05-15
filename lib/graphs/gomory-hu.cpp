struct edge { int u, v; long long w; };
int n; vector <int> p, w, c; vector <edge> tree;
void dfs(int u) {
	c[u] = 1;
	for(const int &id: Dinic::g[u]) {
		int v = Dinic::e[id].b;
		if(!c[v] and Dinic::e[id].flow < Dinic::e[id].cap) dfs(v);
	}
} /* Clears and runs */
vector <edge> run(int _n, const vector <edge> &ed) {
	n = _n; tree.clear(); p.resize(n + 1), w.resize(n + 1), c.resize(n + 1);
	for(const auto &e: ed) {
		Dinic::add_edge(e.u, e.v, e.w); Dinic::add_edge(e.v, e.u, e.w);
	}
	p[1] = 0, fill(p.begin() + 2, p.end(), 1);
	for(int i = 2; i <= n; ++i) {
		w[i] = Dinic::dinic(n, i, p[i]);
		fill(c.begin(), c.end(), 0); dfs(i);
		for(int j = i + 1; j <= n; ++j) if(c[j] && p[j] == p[i]) p[j] = i;
		if(p[p[i]] && c[p[p[i]]]) {
			int pi = p[i]; swap(w[i], w[pi]); p[i] = p[pi]; p[pi] = i;
		}
		Dinic::clear_flow();
	}
	for(int i = 1; i <= n; ++i) { if(p[i]) tree.push_back(edge{i, p[i], w[i]}); }
	return tree;
}