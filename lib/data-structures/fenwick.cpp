template < typename TP >
struct Fenwick { // + / sum from 0 to n
	int N = 1e5 + 7; vector < TP > tree;
	Fenwick() { tree.resize(N + 2, 0); }
	Fenwick(int n) : N(n + 2) { tree.resize(N + 2, 0); }
	void update(int id, TP val) {
		for(int i = id + 1; i <= N + 1; i += (i & -i)) tree[i] += val;
	}
	TP pref(int x) {
		TP res = 0;
		for(int i = x + 1; i; i -= (i & -i)) res += tree[i];
		return res;
	}
	TP query(int l, int r) { return pref(r) - pref(l - 1); }
}; /* 2D Fenwick, */
int MAX_X = 1e5, MAX_Y = 1e5; /* map of pair is also fine */
unordered_map < int, unordered_map < int, LL > > tree;
inline void update(int x, int y, LL val) {
    for(int i = x + 1; i <= MAX_X + 1; i += (i & -i))
        for(int j = y + 1; j <= MAX_Y + 1; j += (j & -j)) tree[i][j] += val;
}
inline LL pref(int x, int y) {
    LL res = 0;
    for(int i = x + 1; i; i -= (i & -i)) {
        if(tree.find(i) == tree.end()) continue;
        for(int j = y + 1; j; j -= (j & -j))
            if(tree[i].find(j) != tree[i].end()) res += tree[i][j];
    }
    return res;
}
inline LL query(int x1, int x2, int y1, int y2) {
    return pref(x2, y2) - pref(x2, y1 - 1) - pref(x1 - 1, y2) + pref(x1 - 1, y1 - 1);
}