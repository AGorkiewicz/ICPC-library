typedef long long T;
struct fraction {
    T a, b; // a / b
    fraction(T _a, T _b) : a(_a), b(_b) {
        T g = gcd(abs(a), abs(b));
        a /= g, b /= g;
        if(b < 0)
            a *= -1, b *= -1;
        if(b == 0)
            a = 1;
    }
    fraction operator+ (fraction f) {
        return fraction(a * f.b + f.a * b, b * f.b);
    }
    fraction operator- (fraction f) {
        return fraction(a * f.b - f.a * b, b * f.b);
    }
    fraction operator* (fraction f) {
        return fraction(a * f.a, b * f.b);
    }
    fraction operator/ (fraction f) {
        return fraction(a * f.b, b * f.a);
    }
};
bool operator< (fraction p, fraction q) {
    return p.a * q.b < p.b * q.a;
}
bool operator== (fraction p, fraction q) {
    return p.a * q.b == p.b * q.a;
}