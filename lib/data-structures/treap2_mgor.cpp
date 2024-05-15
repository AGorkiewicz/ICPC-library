#include <bits/stdc++.h>

using namespace std;

struct treap{
    treap *left = 0, *right = 0;
    treap *parent = 0;
    int sz = 1;
    int k;
    int rank;
    bool rev = 0;
    treap(int K = 0)
    {
        k = K;
        rank = rand();
    }
    void lazy()
    {
        if(!rev) return;
        swap(left, right);
        if(left) left->rev = !left->rev;
        if(right) right->rev = !right->rev;
        rev = 0;
    }
};

inline int sz(treap *t)
{
    return (t == 0 ? 0 : t->sz);
}

inline void update(treap *t)
{
    t->sz = sz(t->left) + sz(t->right) + 1;
    if(t->left) t->left->parent = t;
    if(t->right) t->right->parent = t;
}

treap *merge(treap *a, treap *b)
{
    if(a == 0) return b;
    if(b == 0) return a;
    if(a) a->lazy();
    if(b) b->lazy();
    if(a->rank > b->rank)
    {
        a->right = merge(a->right, b);
        update(a);
        return a;
    }
    else
    {
        b->left = merge(a, b->left);
        update(b);
        return b;
    }
}

pair < treap*, treap* > split(treap *t, int k)
{
    if(t == 0) return pair < treap*, treap* >(0, 0);
    t->lazy();
    if(k <= sz(t->left))
    {
        auto p = split(t->left, k);
        t->left = p.second;
        update(t);
        if(p.first) p.first->parent = 0;
        return {p.first, t};
    }
    else
    {
        auto p = split(t->right, k - 1 - sz(t->left));
        t->right = p.first;
        update(t);
        if(p.second) p.second->parent = 0;
        return {t, p.second};
    }
}

treap *insert(treap *t, int k, int x)
{
    auto p = split(t, k);
    return merge(merge(p.first, new treap(x)), p.second);
}

treap *erase(treap *t, int k)
{
    auto p1 = split(t, k);
    auto p2 = split(p1.second, 1);
    delete p2.first;
    return merge(p1.first, p2.second);
}

treap *reverse(treap *t, int a, int b) // <a, b>
{
    auto p1 = split(t, b + 1);
    auto p2 = split(p1.first, a);
    if(p2.second) p2.second->rev = !p2.second->rev;
    return merge(merge(p2.first, p2.second), p1.second);
}

void propagate_up(treap *t)
{
    if(t == 0) return;
    propagate_up(t->parent);
    t->lazy();
}

int nr(treap *t)
{
    if(t->parent == 0) return sz(t->left);
    treap *f = t->parent;
    if(f->left == t)
        return nr(f) - sz(t->right) - 1;
    else
        return nr(f) + sz(t->left) + 1;
}

void print(treap *t)
{
    if(t == 0) return;
    t->lazy();
    print(t->left);
    printf("%d ", t->k + 1);
    print(t->right);
}

const int N = 3e5 + 7;

int n;
treap *A[N], *root;

int main()
{
    scanf("%d", &n);
    for(int i = 0; i < n; i++)
    {
        int x; scanf("%d", &x);
        x--;
        A[x] = new treap(x);
        root = merge(root, A[x]);
    }
    for(int i = 0; i < n; i++)
    {
        propagate_up(A[i]);
        int ans = nr(A[i]);
        printf("%d ", ans + 1);
        root = reverse(root, i, ans);
    }
    return 0;
}
