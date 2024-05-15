struct Matching {
    int n; vector < int > *G, match, vis;
    bool dfs(int v) {
        vis[v] = 1;
        for(auto u: G[v]) if(!match[u] || (!vis[match[u]] && dfs(match[u]))) {
                match[v] = u; match[u] = v; return true;
        }
        return false;
    }
    Matching(int N, vector < int > *g) : n(N), G(g) {
        match.resize(n + 1, 0), vis.resize(n + 1, 0); bool ok = 1;
        while(ok) {
            ok = 0;
            for(int i = 1; i <= n; i++) if(!match[i] && dfs(i)) ok = 1;
            for(int i = 1; i <= n; i++) vis[i] = 0;
        }
    }
};
