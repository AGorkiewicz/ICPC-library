typedef long long T;
int n, invn;
T mod;
void convolve(T *tab, vector<vector<int>> M) {
    for(int i = 1; i < n; i *= 2)
        for(int j = 0; j < n; j += 2 * i)
            for(int k = 0; k < i; k++)
            {
                T &a = tab[j + k], &b = tab[j + i + k];
                T na = (M[0][0] * a + M[0][1] * b) % mod, nb = (M[1][0] * a + M[1][1] * b) % mod;
                a = na; b = nb;
            }
}
void mult(T *a, T *b, T *c) {
    for(int i = 0; i < n; i++)
        c[i] = a[i] * b[i] % mod;
}
//tych funkcji uzywac
//N MUSI byc potega dwojki
void init(int N, T Mod) {
    mod = Mod;
    n = N;
    invn = inv(n); //Trzeba sobie napisać funkcję inv, która liczy odwrotność modulo
}
//UWAGA modyfikuje tablice a i b, robic kopie jesli potrzebne pozniej
void xor_conv(T *a, T *b, T *res) {
    convolve(a, { { 1, 1 }, { 1, -1 } });
    if(a != b) convolve(b, { { 1, 1 }, { 1, -1 } });
    mult(a, b, res);
    convolve(res, { { 1, 1 }, { 1, -1 } });
    for(int i = 0; i < n; i++)
        res[i] = res[i] * invn % mod;
}
void and_conv(T *a, T *b, T *res) {
    convolve(a, { { 0, 1 }, { 1, 1 } });
    if(a != b) convolve(b, { { 0, 1 }, { 1, 1 } });
    mult(a, b, res);
    convolve(res, { { -1, 1 }, { 1, 0 } });
}
void or_conv(T *a, T *b, T *res) {
    convolve(a, { { 1, 0 }, { 1, 1 } });
    if(a != b) convolve(b, { { 1, 0 }, { 1, 1 } });
    mult(a, b, res);
    convolve(res, { { 1, -1 }, { 0, 1 } });
}