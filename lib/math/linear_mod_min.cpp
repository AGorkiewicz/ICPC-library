template <typename T> /* min {ax + b mod m | 0 <= x < n } */
T go(T n, const T &m, T a, T b, bool is_min = true, T p = 1, T q = 1) {
    if (a == 0) return b;
    if (is_min) {
        if (b >= a) {
            T t = (m - b + a - 1) / a;
            T c = (t - 1) * p + q;
            if (n <= c) return b;
            n -= c; b += a * t - m;
        } b = a - 1 - b;
    } else {
        if (b < m - a) {
            T t = (m - b - 1) / a;
            T c = t * p;
            if (n <= c) return a * ((n - 1) / p) + b;
            n -= c; b += a * t;
        } b = m - 1 - b;
    }
    T d = m / a;
    T c = go(n, a, m % a, b, !is_min, (d - 1) * p + q, d * p + q);
    return is_min ? a - 1 - c : m - 1 - c;
}