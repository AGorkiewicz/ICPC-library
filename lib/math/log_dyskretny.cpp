#include <bits/stdc++.h>
#define MP make_pair
using namespace std;

typedef long long LL;
typedef pair < LL, LL > PLL;

// a, b <= 1e9, b < n, n - liczba pierwsza

LL a, b, n, sq;
set < PLL > S;

LL POW(LL x, LL y)
{
    if(y == 0) return 1;
    LL r = POW(x, y / 2);
    r = (r * r) % n;
    return y & 1 ? (r * x) % n : r;
}

int main()
{
    scanf("%lld%lld%lld", &a, &b, &n);
    if(a % n == 0)
    {
        b == 0 ? puts("1") : puts("-1");
        return 0;
    }
    sq = sqrt(n) + 1;
    LL p = 1;
    for(LL i = 0; i < sq; i++)
    {
        S.insert(MP(p, i));
        p = (p * a) % n;
    }
    for(LL i = 0; i < sq; i++)
    {
        LL t = POW(a, n - 2);
        t = (b * POW(t, sq * i)) % n;
        set < PLL > :: iterator it = S.lower_bound(MP(t, 0));
        if(it != S.end())
        {
            if(t != it -> first) continue;
            printf("%lld\n", sq * i + it -> second);
            return 0;
        }
    }
    puts("-1");
    return 0;
}
