//wynik dla palindromu parzystego o środku między pozycjami i, i + 1 znajduje się 2 * i + 1
//wynik dla palindromu nieparzystego o środku na pozycji i znajduje się w 2 * i
struct manacher{
	int n;
	string s;
	vector <int> rad;
	void init(int N, string &in){
		n = N;
		s.resize(n + n);
		rad.resize(n + n);
		for(int i = 0; i < n + n; ++i)
			s[i] = '#';		//znak niewystepujacy w tekscie
		for(int i = 0; i < n; ++i)
			s[i + i] = in[i];
	}
	void go(){
		int m = 2 * n - 1;
		int x = 0;	
		for(int i = 1; i < m; ++i){
			int &r = rad[i] = 0;
			if(i <= x + rad[x])	
				r = min(rad[x + x - i], x + rad[x] - i);
			while(i - r - 1 >= 0 && i + r + 1 < m && s[i - r - 1] == s[i + r + 1])	
				++r;
			if(i + r >= x + rad[x])	
				x = i;
		}
		for(int i = 0; i < m; ++i){
			if(i - rad[i] == 0 || i + rad[i] == m - 1)	
				++rad[i];
			rad[i] /= 2;
		}
	}
};