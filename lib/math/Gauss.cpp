typedef double T;
const T eps = 1e-8;
int n; vector <T> ans; vector <vector <T> > in;
void init(int _n, vector <vector <T> > _in, vector <T> _ans) {
	n = _n; in = _in; ans = _ans;		
}

bool solve(){	//zwraca czy uklad jest rozwiazywalny
	for(int i = 0; i < n; ++i){
		int id = i;
		for(int j = i + 1; j < n; ++j)
			if(abs(in[j][i]) > abs(in[id][i])) id = j;
		if(abs(in[id][i]) < eps) return false;
		for(int j = 0; j < n; ++j) swap(in[i][j], in[id][j]);
		swap(ans[i], ans[id]);
		for(int j = i + 1; j < n; ++j){
			if(abs(in[j][i]) < eps) continue;
			T mult = in[j][i] / in[i][i];
			for(int k = i; k < n; ++k) in[j][k] -= mult * in[i][k];
			ans[j] -= mult * ans[i];
		}
	}	
	for(int i = n - 1; i >= 0; --i){
		for(int j = n - 1; j > i; --j) ans[i] -= ans[j] * in[i][j];
		ans[i] /= in[i][i];
	}	
	return true;
}