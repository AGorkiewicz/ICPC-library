struct node {
    typedef int T;
    static const T def = 0;
    node *left = 0, *right = 0, *up = 0, *path_parent = 0;
    T val, agg = def;
    bool rev = false;
    node(T v = def) : val(v) { update(); }
    static int f(int a, int b) {
        return max(a, b);
    }
    void update() {
        agg = f(left ? left->agg : def, f(val, right ? right->agg : def));
    }
    bool left_son() {
        return up->left == this;
    }
    void swap_ups(node *n) {
        n->up = up;
        n->path_parent = path_parent;
        up = n;
        path_parent = nullptr;
        n->update();
        if(n->up) {
            if(n->up->left == this) n->up->left = n;
            else n->up->right = n;
            n->up->update();
        }
    }
    void rot_left() {
        node *n = left;
        left = n->right;
        if(left) left->up = this;
        n->right = this;
        update();
        swap_ups(n);
    }
    void rot_right() {
        node *n = right;
        right = n->left;
        if(right) right->up = this;
        n->left = this;
        update();
        swap_ups(n);
    }
    void rot_up() {
        if(left_son()) up->rot_left();
        else up->rot_right();
    }
    void update_rev() {
        if(up) up->update_rev();
        if(rev) {
            rev = false;
            swap(left, right);
            if(left) left->rev = !left->rev;
            if(right) right->rev = !right->rev;
        }
    }
    node* go_up() {
        update_rev();
        while(up) {
            if(up->up)
                if(up->left_son() == left_son()) {
                    up->rot_up();
                    rot_up();
                }
                else {
                    rot_up();
                    rot_up();
                }
            else rot_up();
        }
        return this;
    }
    node* access() {
        node *last = nullptr;
        node *n = this;
        while(n) {
            n->go_up();
            if(n->left)
                swap(n->left->up, n->left->path_parent);
            n->left = last;
            if(last) swap(last->up, last->path_parent);
            n->update();
            last = n;
            n = n->path_parent;
        }
        go_up();
        return last;
    }
    void link(node *n) {
        access();
        rev = !rev;
        path_parent = n;
    }
    void cut() {
        access();
        if(right) {
            right->up = 0;
            right->path_parent = 0;
            right = 0;
        }
    }
    node* root() {
        access();
        node *n = this;
        while(n->right)
            n = n->right;
        n->go_up();
        return n;
    }
};
node* lca(node *a, node *b) {
    a->access();
    return b->access();
}
node::T on_path(node *a, node *b) {
    node *c = lca(a, b);
    a->go_up();
    c->go_up();
    if(a == c) return c->left->agg;
    if(b == c) return a->agg;
    return node::f(a->agg, c->left->agg);
}
node* insert(node *n, T k) {
    if(n == 0) return new node(k);
    n = n->splay(k);
    node *r = new node(k);
    if(n->val < k) {
        r->right = n->right; n->right = 0;
        if(r->right) r->right->up = r;
        r->left = n; n->up = r;
        n->update(); r->update();
    } else {
        r->left = n->left; n->left = 0;
        if(r->left) r->left->up = r;
        r->right = n; n->up = r;
        n->update(); r->update();
    }
    return r;
}
node* erase(node *n, T k) {
    if(n == 0) return 0;
    n = n->splay(k);
    if(n->val != k) return n;
    if(n->left == 0) {
        if(n->right == 0) return 0;
        n->right->up = 0;
        return n->right;
    }
    n->left->up = 0;
    node *r = n->left->splay(k);
    r->right = n->right;
    if(r->right) r->right->up = r;
    r->update(); delete n; 
    return r;
}