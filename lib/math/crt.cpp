typedef long long T;
pair<T, T> gcd_ext(T a, T b) {
    if(b == 0) return { 1, 0 };
    auto p = gcd_ext(b, a % b);
    return { p.second, p.first - a / b * p.second };
}
pair<T, T> CRT(vector<pair<T, T>> con) {
    T k = 0, m = 1;
    for(auto c: con) {
        T k1 = k, m1 = m, k2 = c.first, m2 = c.second;
        auto q = gcd_ext(m1, m2);
        T gcd = m1 * q.first + m2 * q.second;
        m = m1 / gcd * m2;
        if(k1 % gcd != k2 % gcd) return { -1, -1 };
        k = (k1 / gcd) * m2 * q.second + (k2 / gcd) * m1 * q.first + k1 % gcd;
        k %= m; if(k < 0) k += m;
    }
    return { k, m };
}