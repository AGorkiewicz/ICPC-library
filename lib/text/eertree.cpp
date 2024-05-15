const int N = 1e6 + 5; // CUSTOM
const int A = 26; // CUSTOM
int nxt[N][A], fail[N], last[N], len[N], cnt, par[N];
char s[N];
void prepare(int n){ // 0 <= i <= n + 1
    rep(i, 0, n + 1){
        rep(j, 0, A - 1) nxt[i][j] = 0;
    }
    s[0] = '#'; // CUSTOM
    last[0] = 1;
    cnt = 1;
    fail[0] = fail[1] = 1;
    len[1] = -1;
}
void add(int n){
    int c = s[n] - 'a'; // CUSTOM
    int v = last[n - 1];
    while(s[n - len[v] - 1] != s[n]) v = fail[v];
    if(!nxt[v][c]){
        int now = ++cnt, k = fail[v];
        len[now] = len[v] + 2;
        while(s[n - len[k] - 1] != s[n]) k = fail[k];
        fail[now] = nxt[k][c]; nxt[v][c] = now;
        par[now] = v;
    }
    last[n] = nxt[v][c];
}
