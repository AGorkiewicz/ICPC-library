#pragma GCC optimize ("O3")
#include <bits/stdc++.h>
using namespace std;
#define rep(i, a, b) for (int i = (a); i <= (b); i++)
#define per(i, a, b) for (int i = (b); i >= (a); i--)
#define SZ(x) ((int)x.size())
#define all(x) x.begin(),x.end()
#define pb push_back
#define mp make_pair
#define st first
#define nd second
using ll = long long;
using lf = long double;
using pii = pair <int, int>;
using pll = pair <ll, ll>;
auto& operator<<(auto& o, pair <auto, auto> p){
    return o << "(" << p.first << ", " << p.second << ")";
}
auto operator<<(auto& o, auto x)->decltype(end(x), o){
    o << "{"; int i = 0; for (auto e : x) o << ", " + 2*!i++ << e;
    return o << "}";
}
#define dbg(x...) cerr<<"["#x"]: ",[](auto...$){((cerr<<$<<"; "),...)<<endl;}(x)
