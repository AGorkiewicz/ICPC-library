typedef int T; const int N = 507; const T INF = 1e9 + 7;
int n, max_match;
T cost[N][N], lx[N], ly[N], slack[N], slackx[N];
int xy[N], yx[N], prev[N]; bool S[N], U[N];
void update_labels() {
    T delta = INF;
    FOR(y, n) if(!U[y]) delta = min(delta, slack[y]);
    FOR(x, n) if(S[x]) lx[x] -= delta;
    FOR(y, n) if(U[y]) ly[y] += delta;
    FOR(y, n) if(!U[y]) slack[y] -= delta;
}
void add_to_tree(int x, int f) {
    S[x] = true; prev[x] = f;
    FOR(y, n) if(lx[x] + ly[y] - cost[x][y] < slack[y]) {
        slack[y] = lx[x] + ly[y] - cost[x][y]; slackx[y] = x;
    }
}
void augment() {
    if (max_match == n) return;
    int root, q[N], wr = 0, rd = 0;
    memset(S, false, sizeof(S)); memset(U, false, sizeof(U));
    memset(prev, -1, sizeof(prev));
    FOR(x, n) if(xy[x] == -1) {
        q[wr++] = root = x; prev[x] = -2; S[x] = true; break;
    }
    FOR(y, n) { slack[y] = lx[root] + ly[y] - cost[root][y]; slackx[y] = root; }
    int x, y;
    while(true) {
        while(rd < wr) {
            x = q[rd++];
            for(y = 0; y < n; y++) {
                if(cost[x][y] == lx[x] + ly[y] && !U[y]) {
                    if (yx[y] == -1) break;
                    U[y] = true; q[wr++] = yx[y]; add_to_tree(yx[y], x);
                }
            }
            if(y < n) break;
        }
        if (y < n) break;
        update_labels(); wr = rd = 0;
        for(y = 0; y < n; y++) {
            if(!U[y] && slack[y] == 0) {
                if(yx[y] == -1) { x = slackx[y]; break; }
                else {
                    U[y] = true;
                    if(!S[yx[y]]) {
                        q[wr++] = yx[y]; add_to_tree(yx[y], slackx[y]);
                    }
                }
            }
        }
        if(y < n) break;
    }
    if(y < n) {
        max_match++;
        for(int cx = x, cy = y, ty; cx != -2; cx = prev[cx], cy = ty) {
            ty = xy[cx]; yx[cy] = cx; xy[cx] = cy;
        }
        augment();
    }
}
T maxCostMatching() {
    T res = 0; max_match = 0;
    FOR(i, n) xy[i] = yx[i] = -1, lx[i] = ly[i] = 0;
    FOR(x, n) FOR(y, n) lx[x] = max(lx[x], cost[x][y]);
    augment(); FOR(x, n) res += cost[x][xy[x]];
    return res;
}