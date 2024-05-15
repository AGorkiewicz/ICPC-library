ll f(ll p, ll cnt, ll k) { /* distinct a^k % p^cnt over all a, prime p */
  if (cnt <= 0 or k == 0) return 1; /* O(cnt^2), optimize with precalc power */
  if (p == 2) {
    if (cnt == 1) return 2;
    ll u = power(2, cnt - 2) / __gcd(k, power(2, cnt - 2));
    if (k % 2) u *= 2;
    return u + f(2, cnt - k, k);
  }
  ll phi = power(p, cnt) - power(p, cnt - 1);
  ll u = phi / __gcd(k, phi);
  return u + f(p, cnt - k, k);
}