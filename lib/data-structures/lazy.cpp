struct SegmentTree { /* (+, max) / (*) przy zamianie max->min */
    const static int MAX = 1 << 20; LL INF = 1e18 + 7;
    vector < PLL > tree; vector < LL > lazy;
    SegmentTree() {
        tree.resize(2 * MAX, {0, 0}), lazy.resize(2 * MAX, 0);
        for(int i = 0; i <= MAX - 1; i++)
            tree[i + MAX].second = i;
        for(int i = MAX - 1; i; i--)
            tree[i] = max(tree[2 * i], tree[2 * i + 1]); // (*)
    }
    inline void propagate(int node, int l, int r) {
        if(!lazy[node]) return;
        tree[node].first += lazy[node];
        if(l != r) {
            lazy[2 * node] += lazy[node];
            lazy[2 * node + 1] += lazy[node];
        }
        lazy[node] = 0;
    }
    void update(int a, int b, LL val, int node = 1, int l = 0, int r = MAX - 1) {
        propagate(node, l, r);
        if(b < l || r < a) return;
        if(a <= l && r <= b)
            lazy[node] += val, propagate(node, l, r);
        else {
            update(a, b, val, 2 * node, l, (l + r) / 2);
            update(a, b, val, 2 * node + 1, (l + r) / 2 + 1, r);
            tree[node] = max(tree[2 * node], tree[2 * node + 1]); // (*)
        }
    }
    PLL query(int a, int b, int node = 1, int l = 0, int r = MAX - 1) {
        propagate(node, l, r);
        if(b < l || r < a) return {-INF, 0}; // (*)
        if(a <= l && r <= b) return tree[node];
        return max(query(a, b, 2 * node, l, (l + r) / 2), query(a, b, 2 * node + 1, (l + r) / 2 + 1, r)); // (*)
    }
};