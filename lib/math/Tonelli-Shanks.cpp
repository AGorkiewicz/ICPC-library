int get(int p){
	int t = 2;
	while(fast(t, (p - 1) / 2, p) == 1) ++t;
	return t;
}
int dsr(int v, int p){	//sqrt(p) mod p, p is prime, -1 no solution
	if(v == 0) return 0;
	if(p == 2) return 1;
	if(fast(v, (p - 1) / 2, p) == p - 1) return -1;
	int q = p - 1, s = 0;
	while(!(q & 1)) q /= 2, ++s;
	if(s == 1) return fast(v, (p + 1) / 4, p);
	int z = get(p), m = s, t = fast(v, q, p);
	int c = fast(z, q, p), r = fast(v, (q + 1) / 2, p);
	while(t != 1){
		int tt = t, i = 0;
		while(tt != 1) { tt = (1LL * tt * tt)%p, ++i; }
		int b = fast(c, fast(2, m - i - 1, p - 1), p);
		int b2 = (1LL * b * b)%p;
		r = (1LL * r * b)%p;
		t = (1LL * t * b2)%p;
		c = b2, m = i;
	}
	return r;
}