template < typename TP >
struct pSegmentTree {
	LL MAX;
	TP init;
	struct node {
		TP val;
		node *left = nullptr, *right = nullptr;
		LL l, r;
		node(LL L, LL R, TP v) : val(v), l(L), r(R) {}
	};
	vector < node* > roots;
	pSegmentTree(LL n, TP zero) : init(zero) { MAX = 1LL << (64 - __builtin_clzll(n)); roots.push_back(new node(0, MAX - 1, init)); }
	void check(node *root) {
		LL m = (root -> l + root -> r) / 2;
		if(root -> left == nullptr)
			root -> left = new node(root -> l, m, init);
		if(root -> right == nullptr)
			root -> right = new node(m + 1, root -> r, init);
	}
	node *add(node *root, LL id, TP v) {
		node *res = new node(*root);
		res -> val += v;
		if(res -> l == res -> r) return res;
		LL m = (res -> l + res -> r) / 2;
		check(res);
		if(id <= m)
			res -> left = add(res -> left, id, v);
		else
			res -> right = add(res -> right, id, v);
		return res;
	}
	TP ask(node *root, LL a, LL b) {
		if(root -> r < a || b < root -> l) return init;
		if(a <= root -> l && root -> r <= b) return root -> val;
		check(root);
		return ask(root -> left, a, b) + ask(root -> right, a, b);
	}
	void update(LL id, TP v, int state = -1) {
		if(state == -1) state += sz(roots);
		assert(state < sz(roots));
		roots.push_back(add(roots[state], id, v));
	}
	TP query(LL a, LL b, int state = -1) {
		if(state == -1) state += sz(roots);
		assert(state < sz(roots));
		return ask(roots[state], a, b);
	}
};
// dla przedzialu [l, r] odpowiada ile liczb jest k : a <= k <= b
// l, r, a, b <= 1e6, 1-indexed, n*log(n)
struct TwoDimensional {
	int n, *t;
	pSegmentTree < int > *tree;
	TwoDimensional(int N, int *T) : n(N), t(T) {
		tree = new pSegmentTree < int > (n, 0);
		for(int i = 1; i <= n; i++)
			tree -> update(t[i], 1);
	}
	int query(int l, int r, int a, int b) {
		return tree -> query(a, b, r) - tree -> query(a, b, l - 1);
	}
};
