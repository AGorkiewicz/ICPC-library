string min_cyclic_string(string s) {
    s += s; int n = s.size(), i = 0, ans = 0;
    while (i < n / 2) {
        ans = i; int j = i + 1, k = i;
        while (j < n && s[k] <= s[j]) {
            k = s[k] < s[j] ? i : k + 1; j++;
        }
        while (i <= k) i += j - k;
    }
    return s.substr(ans, n / 2);
}