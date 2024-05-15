const int maxv = 40;
const int maxp = 400'007;
inline LL mod(LL a, LL n){
	if(a >= n)	a -= n; return a;
}
inline LL add(LL a, LL b, LL n){
	a += b; mod(a, n); return a;
}
inline LL mul(LL x, LL y, LL p) {
	LL ret = x * y - (LL)((long double)x * y / p + 0.5) * p;
	return ret < 0 ? ret + p : ret;
}
LL fast(LL x, LL k, LL p){
	LL ret = 1%p;
	for(; k > 0; k >>= 1, x = mul(x, x, p))
		(k & 1) && (ret = mul(ret, x, p));
	return ret;
}
LL factor(LL n) { /* finds a divisor of n */
	static LL seq[maxp];
	while(true){
		LL x = rand()%n, y = x, c = rand()%n;
		LL *px = seq, *py = seq, tim = 0, prd = 1;	
		while(true){
			*py++ = y = add(mul(y, y, n), c, n);
			*py++ = y = add(mul(y, y, n), c, n);
			if((x = *px++) == y) break;
			LL tmp = prd;
			prd = mul(prd, abs(y - x), n);
			if(!prd) return gcd(tmp, n);
			if((++tim) == maxv){
				if((prd = gcd(prd, n)) > 1 && prd < n) return prd;
				tim = 0;
			}
		}
		if(tim && (prd = gcd(prd, n)) > 1 && prd < n) return prd;
	}
}