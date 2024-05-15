struct AhoCorasick {
    typedef long long T;
    const int A = 14;
    const int off = 'a';
    int n = 0;
    vector<int> fail, father, letter, ord;
    vector<vector<int>> go;
    vector<T> value;
    AhoCorasick() {
        father.resize(1, -1);
        letter.resize(1);
        value.resize(1);
        go.resize(1, vector<int>(A));
    }
    void add(const string &s, T mult = 1) {
        int node = 0;
        for(auto c: s) {
            if(!go[node][c - off]) {
                go[node][c - off] = ++n;
                go.push_back(vector<int>(A));
                fail.push_back(0);
                father.push_back(node);
                letter.push_back(c - off);
                value.push_back(0);
            }
            node = go[node][c - off];
        }
        value[node] += mult;
    }
    void create_automaton() {
        queue<int> Q; Q.push(0);
        fail.resize(n + 1);
        while(!Q.empty()) {
            int node = Q.front(); Q.pop();
            if(node != 0 && father[node] != 0)
                fail[node] = go[fail[father[node]]][letter[node]];
            for(int i = 0; i < A; i++) {
                if(node != 0 && go[node][i] == 0)
                    go[node][i] = go[fail[node]][i];
                else if(go[node][i] != 0)
                    Q.push(go[node][i]);
            }
        }
    }
};
