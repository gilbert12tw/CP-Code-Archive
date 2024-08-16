#include<bits/stdc++.h>
#define pb push_back
#define sz(x) (int)(x.size())
#define all(x) x.begin(), x.end()
#define int long long
#define pii pair<int, int>
#define inf 0x3f3f3f3f
#define ar array
#define mod 1000000007
#define F first
#define S second
#define wopen(x) freopen((x),"w",stdout)
#define ropen(x) freopen((x),"r",stdin)
#define de(x) cout << #x << " = " << x << ' ';
#define io ios_base::sync_with_stdio(0); cin.tie(0);
using namespace std;
const int mxN = 2e6 + 5;
 
int n, m;
 
int J[mxN], invJ[mxN];
 
int fp(int a, int b, int p) {
    int res = 1;
    while(b) {
        if(b&1) res = (res * a) % p;
        a = a * a % p;
        b >>= 1;
    }
    return res;
}
 
void build(int n) {
    J[1] = J[0] = invJ[1] = invJ[0] = 1;
    for(int i = 2; i <= n; i++) J[i] = J[i - 1] * i % mod;
    invJ[n] = fp(J[n], mod - 2, mod);
    for(int i = n - 1; i >= 2; i--) invJ[i] = invJ[i + 1] * (i + 1) % mod;
}
 
int C(int n, int m) {
    if(n == m or m == 0) return 1;
    int res = J[n] * invJ[n - m] % mod * invJ[m] % mod;
    return res;
}
 
signed main() {
	io;
	cin >> n >> m;
	build(n + m + 1);
	cout << C(n + m - 1, m) << '\n';
}

