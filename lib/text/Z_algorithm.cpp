vector<int> Zalgorithm(string s) {
    int n = s.size(), L = 1, R = 1;
    vector <int> z(n); z[0] = n;
    for (int i = 1; i < n; ++i) {
        if (i + z[i - L] < R) { z[i] = z[i - L]; } 
        else {
            L = i, R = max(R, i);
            while (R < n && s[R] == s[R - i]) R++;
            z[i] = R - i;
        }
    }
    return z;
}