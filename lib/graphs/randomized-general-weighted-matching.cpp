long long G[N][N], dis[N];
int n, top, match[N], mat[N], stk[N], id[N], vis[N];
const long long inf = 1e18;
void init(int _n) {
    n = _n; top = 0; memset(match, 0, sizeof match);
    for (int i = 1; i <= n + 1; i++)
        for (int j = 1; j <= n + 1; j++) G[i][j] = 0;
}
void add_edge(int u, int v, long long w) {
    G[u][v] = max(G[u][v], w); G[v][u] = max(G[v][u], w);
}
bool spfa(int u) {
    stk[top ++] = u;
    if (vis[u]) return true;
    vis[u] = true;
    for (int i = 1; i <= n; ++ i) {
        if (i != u && i != mat[u] && !vis[i]) {
            int v = mat[i];
            if (dis[v] < dis[u] + G[u][i] - G[i][v]) {
                dis[v] = dis[u] + G[u][i] - G[i][v];
                if (spfa(v)) return true;
            }
        }
    }
    top--; vis[u] = false;
    return false;
}
long long maximum_matching() {
    for (int i = 1; i <= n; ++ i) id[i] = i;
    for (int i = 1; i <= n; i += 2) mat[i] = i + 1, mat[i + 1] = i;
    for (int times = 0, flag; times < 3; ) { /* more iters, better prob */
        memset(dis, 0, sizeof(dis)); memset(vis, 0, sizeof(vis));
        top = 0; flag = 0;
        for (int i = 1; i <= n; ++ i) {
            if (spfa(id[i])) {
                flag = 1; int t = mat[stk[top - 1]], j = top - 2;
                while (stk[j] != stk[top - 1]) {
                    mat[t] = stk[j]; swap(t, mat[stk[j]]); --j;
                }
                mat[t] = stk[j]; mat[stk[j]] = t; break;
            }
        }
        if (!flag) { times ++; random_shuffle(id + 1, id + n + 1); }
    }
    long long ans = 0;
    for (int i = 1; i <= n; ++ i) {
        if (mat[i] <= n && i < mat[i]) {
            if (G[i][mat[i]] != 0)
                ans += G[i][mat[i]], match[i] = mat[i], match[mat[i]] = i;
        }
    }
    return ans;
}
