struct twosat { /* 0-indexed */
    int n, cnt; vector <vector <int> > G, R;
    vector <int> order, comp, ans; vector <bool> vis;
    twosat(int _n) : n(_n) {
        G.resize(n + n); R.resize(n + n); comp.resize(n + n); vis.resize(n + n);
        ans.resize(n); order.reserve(n + n);
    }
    void add_edge(int u, int v) { G[u].push_back(v); R[v].push_back(u); }
    void add_clause(int u, bool fu, int v, bool fv) {
        add_edge(u << 1 | !fu, v << 1 | fv); add_edge(v << 1 | !fv, u << 1 | fu);
    }
    void dfs(int u) {
        vis[u] = true;
        for (const auto &v: G[u]) if (!vis[v]) dfs(v);
        order.push_back(u);
    }
    void scc(int u, int id) {
        vis[u] = true, comp[u] = id;
        for (const auto &v: R[u]) if (!vis[v]) scc(v, id);
    }
    bool run() {
        for (int i = 0; i < n + n; ++i) if (!vis[i]) dfs(i);        
        fill(vis.begin(), vis.end(), false);
        reverse(order.begin(), order.end());
        for (const auto &v: order) if (!vis[v]) scc(v, ++cnt);        
        for (int i = 0; i < n; ++i) {
            if (comp[i << 1] == comp[i << 1 | 1])   return false;
            ans[i] = comp[i << 1] < comp[i << 1 | 1];
        }
        return true;
    }
};