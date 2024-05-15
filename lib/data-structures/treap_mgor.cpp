#include <bits/stdc++.h>

using namespace std;

struct treap{
    treap *left = 0, *right = 0;
    int sz = 1;
    int k;
    int rank;
    treap(int K = 0)
    {
        k = K;
        rank = rand();
    }
};

inline int sz(treap *t)
{
    return (t == 0 ? 0 : t->sz);
}

inline void update(treap *t)
{
    t->sz = sz(t->left) + sz(t->right) + 1;
}

treap *merge(treap *a, treap *b)
{
    if(a == 0) return b;
    if(b == 0) return a;
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
    if(k <= sz(t->left))
    {
        auto p = split(t->left, k);
        t->left = p.second;
        update(t);
        return {p.first, t};
    }
    else
    {
        auto p = split(t->right, k - 1 - sz(t->left));
        t->right = p.first;
        update(t);
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

void print(treap *t)
{
    if(t == 0) return;
    print(t->left);
    printf("%d ", t->k);
    print(t->right);
}

int main()
{
    treap *root = 0;
    while(1)
    {
        int a, b; scanf("%d%d", &a, &b);
        if(a == 1)
        {
            int c; scanf("%d", &c);
            root = insert(root, b, c);
        }
        else
        {
            root = erase(root, b);
        }
        print(root);
        printf("\n");
    }
    return 0;
}
