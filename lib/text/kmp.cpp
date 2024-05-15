vector<int> KMP(char *s) {
    int n = strlen(s + 1);
    vector<int> T(n + 1, 0);
    for (int i = 2; i <= n; i++) {
        int t = T[i - 1];
        while (t > 0 && s[i] != s[t + 1]) {
            t = T[t];
        }
        if (s[i] == s[t + 1])
            t++;
        T[i] = t;
    }
    return T;
}