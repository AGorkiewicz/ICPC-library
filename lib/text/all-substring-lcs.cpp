const int N = 2002;
int f[N][N], g[N][N];
void solve(string s, string t)
{
    int  n = s.size(), m = t.size();
    s = "#" + s;
    t = "#" + t;
    for (int i = 1; i <= m; ++i) f[0][i] = i;
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            if (s[i] == t[j]) {
                f[i][j] = g[i][j - 1];
                g[i][j] = f[i - 1][j];
            } 
            else {
                f[i][j] = max(f[i - 1][j], g[i][j - 1]);
                g[i][j] = min(g[i][j - 1], f[i - 1][j]);
            }
        }
    }
    for (int i = 1; i <= m; ++i) {
        for (int j = i, ans = 0; j <= m; ++j) {
            if (i > f[n][j]) ++ans;
            //ans is lcs of s and t[i, j]
        }
    }
}
