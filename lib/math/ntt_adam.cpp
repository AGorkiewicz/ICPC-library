const int mod = 998244353, gen = 3;
void ntt(vector <int>& A){
	int n = A.size();
	static vector <int> roots = {1, 1};
	while (roots.size() < n){
		int s = roots.size();
		roots.resize(2 * s);
		int tmp[] = {1, pw(gen, (mod - 1) / (2 * s))};
		for (int i = s; i < 2 * s; i++){
			roots[i] = 1ll * roots[i / 2] * tmp[i % 2] % mod;
		}
	}
	for (int i = 1, j = 0; i < n; i++){
		j ^= n - (1 << __lg(n - j - 1));
		if (i < j) swap(A[i], A[j]);
	}
	for (int k = 1; k < n; k *= 2){
		for (int i = 0; i < n; i += 2 * k){
			for (int j = 0; j < k; j++){
				const int tmp = 1ll * roots[j + k] * A[i + j + k] % mod;
				A[i + j + k] = A[i + j] + mod - tmp;
				A[i + j] += tmp;
				if (A[i + j] >= mod) A[i + j] -= mod;
				if (A[i + j + k] >= mod) A[i + j + k] -= mod;
			}
		}
	}
}
vector <int> convolve(vector <int> A, vector <int> B){
	if (A.empty() || B.empty()) return {};
	int s = A.size() + B.size() - 1;
	int n = 1 << (__lg(s - 1) + 1);
	int inv = pw(n, mod - 2);
	A.resize(n), ntt(A);
	B.resize(n), ntt(B);
	vector <int> C(n);
	for (int i = 0; i < n; i++){
		C[-i & (n - 1)] = 1ll * A[i] * B[i] % mod * inv % mod;
	}
	ntt(C);
	C.resize(s);
	return C;
}