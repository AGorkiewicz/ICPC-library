/* 2, 7, 61 are enough for n < 2^32, helpers in Rho-Pollard */
bool rabin(LL n){ /* [pr] is a table of primes */
	if(n == 2) return 1;
	if(n < 2 || !(n & 1)) return false;
	LL s = 0, r = n - 1;
	for(; !(r & 1); r >>= 1, ++s);
	for(int i = 0; pr[i] < n && pr[i] < maxv; ++i) {
		LL cur = fast(pr[i], r, n), nxt;
		for(int j = 0; j < s; ++j) {
			nxt = mul(cur, cur, n);
			if(nxt == 1 && cur != 1 && cur != n - 1) return false;
			cur = nxt;
		}
		if(cur != 1) return false;
	}
	return true;
}