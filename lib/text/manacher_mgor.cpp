#include <bits/stdc++.h>
using namespace std;

const int N = 1e6 + 7;

int n, R[N], Q[N];
char s[N];

void Manacher_P()
{
    s[0] = '#', s[n + 1] = '!';
    int i = 1, t = 0;
    while(i <= n)
    {
        while(s[i - t] == s[i + t + 1]) t++;
        R[i] = t;
        int k = 1;
        while(k <= t && R[i] - k != R[i - k])
        {
            R[i + k] = min(R[i - k], R[i] - k);
            k++;
        }
        t = max(t - k, 0), i += k;
    }
}

void Manacher_NP()
{
    s[0] = '#', s[n + 1] = '!';
    int i = 1, t = 0;
    while(i <= n)
    {
        while(s[i - t - 1] == s[i + t + 1]) t++;
        Q[i] = t;
        int k = 1;
        while(k <= t && Q[i - k] != Q[i] - k)
        {
            Q[i + k] = min(Q[i - k], Q[i] - k);
            k++;
        }
        t = max(t - k, 0), i += k;
    }
}

int main()
{
    scanf("%s", s + 1);
    n = strlen(s + 1);
    Manacher_P();
    Manacher_NP();
    long long res = 0;
    for(int i = 1; i <= n; i++)
        res += R[i] + Q[i] + 1;
    printf("%lld\n", res);
    return 0;
}
