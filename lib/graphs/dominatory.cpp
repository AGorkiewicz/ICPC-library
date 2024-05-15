#define NODES 100007
int parent[NODES+1], ancestor[NODES+1], vertex[NODES+1];
int label[NODES+1], semi[NODES+1];
int dom[NODES+1]; // drzewo dominacji, dom[v] - ojciec v w drzewie, dom[root] = 0
vi succ[NODES+1], pred[NODES+1], bucket[NODES+1];
int czas, N, root;
void czysc (int _N, int _root) {
    N = _N;
    root = _root;
    czas = 0;
    FOR(i,N+1) semi[i] = 0;
    FOR(i,N+1) pred[i].clear();
    FOR(i,N+1) succ[i].clear();
    FOR(i,N+1) bucket[i].clear();
}
void dfs (int v) {
    semi[v] = ++czas;
    label[v] = vertex[czas] = v;
    ancestor[v] = 0;
    for(auto w: succ[v]){
        if (semi[w] == 0) { parent[w] = v; dfs(w); }
        pred[w].push_back(v);
    }
}
void compress (int v) {
    if (ancestor[ancestor[v]] == 0) return;
    compress(ancestor[v]);
    if (semi[label[ancestor[v]]] < semi[label[v]]) label[v] = label[ancestor[v]];
    ancestor[v] = ancestor[ancestor[v]];
}
int eval(int v) {
    if (ancestor[v] == 0) return v;
    compress(v);
    return label[v];
}
void dominacja () {
    dfs(root);
    for(int i = czas; i >= 2; i--) {
        int w = vertex[i];
        for(auto v: pred[w]) {
            int u = eval(v);
            if (semi[u] < semi[w]) semi[w] = semi[u];
        }
        bucket[vertex[semi[w]]].push_back(w);
        ancestor[w] = parent[w];
        for(auto v: bucket[parent[w]]) {
            int u = eval(v);
            dom[v] = (semi[u] < semi[v] ? u : parent[w]);
        }
        bucket[parent[w]].clear();
    }
    for(int i = 2; i <= czas; i++) {
        int w = vertex[i];
        if (dom[w] != vertex[semi[w]]) dom[w] = dom[dom[w]];
    }
    dom[root] = 0;
}
int main() { int n = 10; czysc(n,1); /*dod krawedzie do succ*/ dominacja(); }