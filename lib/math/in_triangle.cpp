LL go(LL n, LL p, LL q) {
    if(n * p < q) return n + 1;
    if(p < q) {
        LL rect = (n + 1) * (n * p / q + 1);
        LL diag = n / q + 1;
        return diag + rect - go(n * p / q, q, p);
    }
    LL k = p / q;
    return k * n * (n + 1) / 2 + go(n, p - k * q, q);
}
LL in_triangle(LL n, LL p, LL q) {
    LL d = __gcd(p, q);
    return go(n, p / d, q / d);
}