const int mod = 998244353;
const int inv2 = (mod + 1) / 2;
struct tran {
	virtual int size() {}
	virtual void apply(int* A, bool inverse, int jump = 1) {}
};
struct xor_tran : tran {
	int size() { return 2; }
	void apply(int* A, bool inverse, int jump = 1)
	{
		int& na = A[0 * jump];
		int& nb = A[1 * jump];
		cint pa = na, pb = nb;
		na = pa + pb, nb = pa - pb;
		// na = pb, nb = pa + pb; and_tran
		// na = -pa + pb, nb = pa; inverse and_tran
		// na = pa + pb, nb = pa; or_tran
		// na = pb, nb = pa - pb; inverse or_tran
		if (na >= mod) na -= mod;
		if (nb < 0) nb += mod;
		if (inverse){
			na = 1ll * na * inv2 % mod;
			nb = 1ll * nb * inv2 % mod;
		}
	}
};
struct sum_tran : tran {
	int n;
	int size() { return n; }
	sum_tran(int s) : n(s) {}
	void apply(int* A, bool inverse, int jump = 1){
		vector <int> vec(n);
		for (int i = 0; i < n; i++) vec[i] = A[i * jump];
		ntt(vec);
		if (inverse){
			int inv = pw(n, mod - 2);
			reverse(vec.begin() + 1, vec.end());
			for (int& a : vec) a = 1ll * a * inv % mod;
		}
		for (int i = 0; i < n; i++) A[i * jump] = vec[i];
	}
};
struct russian : tran // niezależne podkonwolucje (od najmłodszej do najstarszej)
{
	int n;
	vector <tran*> T;
	int size() { return n; }
	russian (vector <tran*> vec = {}){
		T = vec;
		n = 1;
		for (tran* t : T) n *= t->size();
	}
	void apply(int* A, bool inverse, int jump = 1){
		int s = 1;
		for (tran* t : T){
			for (int i = 0; i < this->size(); i += s * t->size()){
				for (int j = 0; j < s; j++){
					t->apply(A + (i + j) * jump, inverse, s * jump);
				}
			}
			s *= t->size();
		}
	}
};
vector <int> convolve(tran* t, vector <int> A, vector <int> B){
	int n = t->size();
	assert(A.size() <= n && B.size() <= n);
	A.resize(n, 0), t->apply(&A[0], false);
	B.resize(n, 0), t->apply(&B[0], false);
	for (int i = 0; i < n; i++){
		A[i] = 1ll * A[i] * B[i] % mod;
	}
	t->apply(&A[0], true);
	return A;
}
