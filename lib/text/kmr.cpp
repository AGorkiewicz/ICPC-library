int n, logn;
vector<int> suf;
vector<vector<int>> kmr_tab;
void init(string input) {
    n = input.size();
    logn = 0;
    kmr_tab.clear();
    vector<int> val(input.begin(), input.end());
    vector<long long> pairs(n);
    suf.resize(n);
    for(int i = 0; i < n; i++)
        suf[i] = i;
    for(int t = 1;; logn++, t *= 2) {
        //zakomentowac jesli niepotrzebne, dodaje n log n do pamieci
        kmr_tab.push_back(val);
        if(t >= n) break;
        for(int i = 0; i < n; i++) {
            pairs[i] = (i + t < n ? val[i+t] : 0) | ((long long)val[i] << 30LL);
        }
        sort(suf.begin(), suf.end(), 
            [&](int a, int b) { return pairs[a] < pairs[b]; });
        int k = 0;
        for(int i = 0; i < n; i++) {
            if(i == 0 || pairs[suf[i]] != pairs[suf[i-1]])
                k++;
            val[suf[i]] = k;
        }
    }
}
int common_prefix(int a, int b) {
    int v = 0;
    for(int i = logn; i >= 0; i--) {
        if(a == n || b == n) break;
        if(kmr_tab[i][a] == kmr_tab[i][b]) {
            int k = 1 << i;
            a += k;
            b += k;
            v += k;
        }
    }
    return v;
}