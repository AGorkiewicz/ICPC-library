typedef long long int LL;

namespace Rabin_Miller{
	const LL P[] = {2, 325, 9375, 28178, 450775, 9780504, 1795265022};

	void mod(LL &a, LL &b){
		if(a >= b)
			a -= b;
	}

	LL RS(LL a, LL b, LL &n){
		LL ret = 0LL;
		while(b){
			if(b & 1){
				ret += a;
				mod(ret, n);
			}

			b >>= 1;
			a += a;
			mod(a, n);
		}

		return ret;
	}
	LL fast(LL a, LL b, LL &n){
		LL ret = 1LL;
		while(b){
			if(b & 1)
				ret = RS(ret, a, n);

			b >>= 1;
			a = RS(a, a, n);
		}

		return ret;
	}

	bool zlozona(LL a, LL d, LL &n, int x){
		LL start = fast(a, d, n);
		if(start == 1)
			return false;

		for(int i = 0; i < x; ++i){
			if(start == n - 1)
				return false;
			start = RS(start, start, n);
		}

		return true;
	}

	bool prime(LL a){
		if(a == 1)
			return false;

		int y = 0;
		LL x = a - 1;	
		while(!(x & 1)){
			++y;
			x >>= 1;
		}

		for(int i = 0; i < 7; ++i)
			if(P[i] == a)
				return true;

		for(int i = 0; i < 7; ++i)
			if(P[i] < a && zlozona(P[i], x, a, y))
				return false;
		return true;
	}
}
