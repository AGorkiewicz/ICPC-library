/*
    minimum value of linear functions
    1 a b - add linear function f(x) = a * x + b
    2 x - find minimum value of f(x), 0 <= x <= 1e6
*/
namespace discreteLinear {
    typedef double T;
    const T INF = 1e15;
    struct line {
        T a, b;
        line(T A = 0, T B = INF) : a(A), b(B) {}
        T val(T x) { return a * x + b; }
    };
    const int MAX = 1 << 20;
    line tree[2 * MAX];
    void update(line f, int node = 1, int l = 0, int r = MAX - 1) {
        if(tree[node].val(l) > f.val(l)) swap(tree[node], f);
        if(tree[node].val(r) < f.val(r)) return;
        int m = (l + r) / 2;
        if(tree[node].val(m) < f.val(m))
            update(f, 2 * node + 1, m + 1, r);
        else
            swap(tree[node], f), update(f, 2 * node, l, m);
    }
    T query(int x, int node = 1, int l = 0, int r = MAX - 1) {
        if(l == r) return tree[node].val(x);
        int m = (l + r) / 2;
        if(x <= m) return min(tree[node].val(x), query(x, 2 * node, l, m));
        return min(tree[node].val(x), query(x, 2 * node + 1, m + 1, r));
    }
}