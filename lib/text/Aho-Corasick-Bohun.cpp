const int N = 1 << 20;
int cnt, fail[N], go[N][26];
void add(string s) {
	int u = 0;
	for (auto ch : s) {
		int c = ch - 'a';
		if (!go[u][c]) go[u][c] = ++cnt;
		u = go[u][c];
	}
}
void build() {
	queue<int> q; q.push(0);
	while (!q.empty()) {
		int u = q.front(); q.pop();
		rep(c, 0, 25) {
			int &v = go[u][c];
			if (v == 0) v = go[fail[u]][c];
			else {
				fail[v] = u == 0 ? 0 : go[fail[u]][c];
				q.push(v);
			}
		}
	}
}