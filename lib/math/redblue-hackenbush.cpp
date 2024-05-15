struct Surreal {
    int value = 0, offset = 0;
    set <int> powers;
    void clear() { value = offset = 0; powers.clear(); }
    int size() { return powers.size(); }
    int sign() {
        const int tmp = 2 * value + !powers.empty();
        return tmp < 0 ? -1 : (tmp > 0);
    }
    int add_power(int power) {
        while (power) {
            if (!powers.count(power - offset)) {
                powers.insert(power - offset); break;
            }
            powers.erase(power - offset); --power;
        }
        return !power;
    }
    void operator += (const Surreal &v) {
        value += v.value;
        for (const int &power: v.powers) {
            value += add_power(power + v.offset);
        }
    }

    void divide(int power) {
        offset += power; int to_add = 0;
        for (int i = 0; i < power; ++i) {
            if (value & 1) { to_add += add_power(power - i); }
            value >>= 1;
        }
        value += to_add;
    }

    void get_next(int t) {
        int power = max(0, -t * value);
        value += t * (power + 1);
        if (value == -1 || (value == 1 && powers.empty())) {
            power++; value += t;
        }
        divide(power);
    }
};
struct RedBlueHack { /* Weights on edges should be -1 or 1 */
    int n;
    vector <int> id;
    vector <Surreal> ans;
    vector <vector <pair <int, int> > > G;
    RedBlueHack(int _n) : n(_n) {
        id.resize(n + 1); iota(id.begin(), id.end(), 0);
        ans.resize(n + 1); G.resize(n + 1);
    }
    void add_edge(int u, int v, int t) {
        G[u].push_back({v, t}); G[v].push_back({u, t});
    }
    void dfs(int u, int p) {
        ans[u].clear();
        for (auto &[v, w]: G[u]) {
            if (v == p) { continue; }
            dfs(v, u); ans[id[v]].get_next(w);
            if (ans[id[u]].size() < ans[id[v]].size()) {
                swap(id[u], id[v]);
            }
            ans[id[u]] += ans[id[v]];
        }
    }
    int run() { dfs(1, 1); return ans[id[1]].sign(); }
};