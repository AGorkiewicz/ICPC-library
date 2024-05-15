mt19937 rnd(time(0)); /* [1, n]*/
vector<int> e[N]; int mate[N], vis[N];
void add(int a, int b) {
    if (a != b) { e[a].push_back(b); e[b].push_back(a); }
}
bool dfs(int a) {
    shuffle(e[a].begin(), e[a].end(), rnd); vis[a] = 1;
    for (auto b : e[a]) {
        int c = mate[b]; if (vis[c]) continue;
        mate[a] = b; mate[b] = a; mate[c] = 0;
        if (!c || dfs(c)) return 1;
        mate[a] = 0; mate[b] = c; mate[c] = b;
    }
    return 0;
}
vector<pair<int, int>> matching(int n) {
    vector<pair<int, int>> res;
    rep(_, 1, 20) {
        memset(mate, 0, sizeof mate);
        rep(i, 1, n) {
            if (!mate[i]) { memset(vis, 0, sizeof vis); dfs(i); }
        }
        vector<pair<int, int>> cur;
        rep(i, 1, n) if (mate[i] > i) cur.push_back({i, mate[i]});
        if (cur.size() > res.size()) res = cur;
    }
    return res;
}