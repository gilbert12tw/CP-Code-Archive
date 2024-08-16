#include<bits/stdc++.h>
#define loli
using namespace std;
typedef long long ll;
#define int ll
#define pii pair<int, int>
#define X first
#define Y second
#define F first
#define S second
#define vi vector<int>
#define SZ(a) ((int)a.size())
#define ALL(v) v.begin(), v.end()
#define pb push_back
#define eb emplace_back
#define push emplace
#define lb(x, v) lower_bound(ALL(x), v)
#define ub(x, v) upper_bound(ALL(x), v)
#define re(x) reverse(ALL(x))
#define uni(x) x.resize(unique(ALL(x)) - x.begin())
#define inf 1000000000
#define INF 1000000000000000000
#define mod 1000000007
#define MOD 998244353
#define get_bit(x, y) ((x>>y)&1)
#define mkp make_pair
#define IO ios_base::sync_with_stdio(0); cin.tie(0);
void abc() {cout << endl;}
template <typename T, typename ...U> void abc(T a, U ...b) {
    cout << a << ' ', abc(b...);
}
#ifdef loli
#define test(args...) abc("[" + string(#args) + "]", args)
#else
#define test(args...) void(0)
#endif

template<class T> bool ckmin(T& a, const T& b) { return b<a ? a=b, 1 : 0; }
template<class T> bool ckmax(T& a, const T& b) { return a<b ? a=b, 1 : 0; }


// ax+ny = 1, ax+ny == ax == 1 (mod n)
void exgcd(int x,int y,int &g,int &a,int &b) {
  if (y == 0) g=x,a=1,b=0;
  else exgcd(y,x%y,g,b,a),b-=(x/y)*a;
}

inline void solve() {
    int x, y;
    cin >> x >> y;
    if (2 % gcd(x, y)) cout << -1 << '\n';
    else {
        int g, a, b;
        exgcd(x, y, g, a, b);
        b *= -1;
        if (abs(g) == 1) a *= 2, b *= 2;
        swap(a, b);
        cout << a << ' ' << b << ' ';
    }
}

signed main() {
	IO;	
	solve();	
}
