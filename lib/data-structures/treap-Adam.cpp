struct treap /* treap z zad odwr sort */ {
	struct node {
		node *l, *r;
		int val, min, rev, size, rank;
		node (int val = 0) : val(val), min(val), rev(false), l(NULL), r(NULL), size(1), rank(rand()) {}
	};
	node pool[1000005];
	int head = 0;
	node* mynew (int val){
		pool[head] = node(val);
		return pool + head ++;
	}
	node* root = NULL;
	int size(node* u) { return u == NULL ? 0 : u->size; }
	int min(node* u) { return u == NULL ? 1e9 : u->min; }
	void pull(node* u){
		u->size = 1 + size(u->l) + size(u->r);
		u->min = std::min(u->val, std::min(min(u->l), min(u->r)));
	}
	void push(node* u){
		if (u->rev){
			swap(u->l, u->r);
			if (u->l != NULL) u->l->rev ^= 1;
			if (u->r != NULL) u->r->rev ^= 1;
			u->rev = false;
		}
	}
	pair <node*, node*> split(node* u, int k){
		if (u == NULL) return {NULL, NULL};
		push(u);
		if (k <= size(u->l)){
			auto p = split(u->l, k);
			u->l = p.s;
			pull(u);
			return {p.f, u};
		} else {
			auto p = split(u->r, k - size(u->l) - 1);
			u->r = p.f;
			pull(u);
			return {u, p.s};
		}
	}
	node* merge(node* a, node* b){
		if (a == NULL) return b;
		if (b == NULL) return a;
		push(a); push(b);
		if (a->rank > b->rank){
			a->r = merge(a->r, b);
			pull(a);
			return a;
		} else {
			b->l = merge(a, b->l);
			pull(b);
			return b;
		}
	}
	void push_back(int val){
		root = merge(root, mynew(val));
	}
	void pop_front(){
		root = split(root, 1).s;
	}
	int find_min(){
		int res = 0;
		node* u = root;
		push(u);
		while (u->val != u->min){
			push(u);
			if (min(u->l) < min(u->r))
				u = u->l;
			else {
				res += size(u->l) + 1;
				u = u->r;
			}
		}
		push(u);
		res += size(u->l);
		return res;
	}
	void reverse_pref(int k){
		auto p = split(root, k);
		p.f->rev ^= 1;
		root = merge(p.f, p.s);
	}
};
