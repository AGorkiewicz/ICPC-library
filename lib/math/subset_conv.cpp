typedef long long T;
const int B = 17, N = 1 << B;
const T mod = 1000000007;
T tA[B+1][N];
T tB[B+1][N];
T conv[B+1][N];
int cnt[N];
void sum_over_subset(T *a, T *b, int k = -1)
{
    for(int i = 0; i < N; i++)
        b[i] = (k == -1 || k == cnt[i]) * a[i];
    for(int i = 0; i < B; i++)
        for(int j = 0; j < N; j++)
            if(j & (1 << i))
                b[j] += b[j ^ (1 << i)];
    for(int i = 0; i < N; i++)
        b[i] %= mod;
}
void mobius_transform(T *a, T b[B+1][N])
{
    for(int i = 0; i <= B; i++)
        sum_over_subset(a, b[i], i);
}  
void subset_conv(T *a, T *b, T *res)
{
    for(int i = 0; i < N; i++)
        cnt[i] = __builtin_popcount(i);
    mobius_transform(a, tA);
    if(a != b)
        mobius_transform(b, tB);
    else copy(tA[0], tA[0] + (B+1)*N, tB[0]);
    for(int i = 0; i <= B; i++)
        for(int j = 0; j < N; j++)
            conv[i][j] = 0;
    for(int i = 0; i <= B; i++)
        for(int j = 0; i + j <= B; j++)
            for(int k = 0; k < N; k++)
            {
                conv[i+j][k] += tA[i][k] * tB[j][k];
                if(conv[i+j][k] >= (1LL << 62))
                    conv[i+j][k] %= mod;
            }
    for(int i = 0; i <= B; i++)
        for(int j = 0; j < N; j++)
        {
            conv[i][j] %= mod;
            if(cnt[j] & 1)
                conv[i][j] *= -1;
        }
    for(int i = 0; i <= B; i++)
        sum_over_subset(conv[i], conv[i]);
    for(int i = 0; i < N; i++)
    {
        res[i] = conv[cnt[i]][i];
        if(cnt[i] & 1)
            res[i] *= -1;
    }
}