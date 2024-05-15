int n, T; /* Call init first, then set ground, then add edges */
vector <int> G[N];
int id[N], low[N], pre[N];
void set_ground(int u) { id[u] = 0; }
void add_edge(int u, int v) {
    G[id[u]].push_back(id[v]);
    if (id[u] != id[v]) G[id[v]].push_back(id[u]);
}
int dfs(int u, int p) {
    int ans = 0;
    pre[u] = low[u] = ++T;
    for (const int &v: G[u]) {
        if (v == p) { p = -1; }
        else if (pre[v] == 0) {
            int res = dfs(v, u);
            low[u] = min(low[u], low[v]);
            ans ^= low[v] > pre[u] ? res + 1 : (res ^ 1);
        } else if (pre[v] < pre[u]) {
            low[u] = min(low[u], pre[v]);
        } else { ans ^= 1; }
    }
    return ans;
}
void init(int _n) { n = _n; iota(id + 1, id + n + 1, 1); }
int run() { return dfs(0, -1); }