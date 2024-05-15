struct aho {
	static const int A = 26;
	static const int off = 'a';
	
	int n;
	vector <int> par, fail;
	vector <char> last;
	vector <vector <int> > nxt;	//mozna mape przy duzym alfabecie
	
	aho() {
		n = 0;
		par = { 0 };
		nxt = { vector <int> (A, -1) };
		last = { 0 };
		fail = { };
	}
	
	int create(int parent, char letter) {
		++v;
		nxt.push_back(vector <int> (A, -1));
		par.push_back(parent);
		last.push_back(letter);
		return v;
	}
	
	void add(string &s) {
		int cur = 0;
		for(auto c: s) {
			if(nxt[cur][c - off] == -1)
				nxt[cur][c - off] = create(cur, c);
			cur = nxt[cur][c - off];
		}
	}
	
	void make() {
		queue <int> Q;
		Q.push(0);
		
		fail.resize(n + 1);
		while(!Q.empty()) {
			int u = Q.front();
			Q.pop();
			
			fail[u] = u ? nxt[fail[par[u]]][last[u]] : 0;
			for(int i = 0; i < A; ++i)
				if(nxt[u][i] == -1)
					nxt[u][i] = u ? nxt[fail[u]][i] : 0;
				else
					Q.push(nxt[u][i]);
		}
	}
};
