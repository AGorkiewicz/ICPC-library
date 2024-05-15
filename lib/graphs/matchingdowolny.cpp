#define N 307
int n;                 // IN: liczba wierzcholkow
bool edge[N][N];       // IN: macierz sasiedztwa (mozna zmienic na liste)
int mate[N];           // OUT: wierzcholek skojarzony (-1 oznacza brak)
int label[N], base[N], prev1[N], prev2[N];
bool mark[N];
bool prepare (int v) {
    while(1) {
        mark[v] = !mark[v];
        if (mate[v] == -1) return mark[v];
        v = base[prev2[mate[v]]];
    }
}
int shrink (int v, int b1, int b2, queue<int> &Q) {
    while (mark[v]) {
        prev1[v] = b1; prev2[v] = b2;
        mark[mate[v]] = 1;
        Q.push(mate[v]);
        v = base[prev2[mate[v]]];
    }
    return v;
}
bool make_blos (int i, int j, int bi, int bj, queue<int> &Q) {
    if (label[i]!=1 || i==j) return 0;
    if (prepare(i), prepare(j)) return 1;
    int b = (shrink(i, bi, bj, Q), shrink(j, bj, bi, Q));
    FOR(v,n) if (mark[base[v]]) base[v] = b;
    return 0;
}
void rematch(int i, int j) {
    int nxt = mate[i];
    mate[i] = j;
    if (nxt==-1) return;
    mate[nxt] = -1;
    rematch(prev2[nxt], prev1[nxt]);
    rematch(prev1[nxt], prev2[nxt]);
}
bool augment() {
    queue<int> Q;
    FOR(i,n) {
        label[i] = mate[i]==-1;
        if (mate[i]==-1) Q.push(i);
        mark[i] = 0;
        base[i] = i;
    }
    while (!Q.empty()) {
        int cur = Q.front(); Q.pop();
        FOR(i,n) /*tu zmienic*/ if (edge[cur][i] && i!=mate[cur]) {
            if (!label[i]) {             // (nie wiem co "zmienic", dziala jak jest)
                label[i] = -1;
                label[mate[i]] = 1;
                Q.push(mate[i]);
                prev1[i] = i; prev2[i] = cur;
            } else if (make_blos(base[i], base[cur], i, cur, Q)) {
                rematch(i, cur); rematch(cur, i);
                return 1;
            }
        }
    }
    return 0;
}
int compute_gcm() { // zwraca licznosc maksymalnego skojarzenia
    fill_n(mate, n, -1);
    int res = 0;
    while (augment()) ++res;
    return res;
}