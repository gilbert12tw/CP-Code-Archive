#include<bits/stdc++.h>
#pragma GCC optimize("Ofast")
#pragma loop-opt(on)
#define pb push_back
#define sz(x) (int)(x.size())
#define all(x) x.begin(), x.end()
#define int long long
#define pii pair<int, int>
#define inf 1e9
#define mod 1000000007
#define F first
#define S second
#define wopen(x) freopen((x),"w",stdout)
#define ropen(x) freopen((x),"r",stdin)
#define de(x) cout << #x << " = " << x << ' '
#define IO ios_base::sync_with_stdio(0); cin.tie(0);
using namespace std;

const int mxN = 2e6 + 5;
int n, m, d[mxN], p = 29;
string s;
int seg[mxN * 4], rseg[mxN * 4];

#define ls (x<<1)
#define rs (ls|1)
#define mid ((l+r)>>1)

void up(int x, int l, int r) {
    seg[x] = (seg[ls] * d[r - mid] % mod + seg[rs]) % mod;
    rseg[x] = (rseg[ls] + rseg[rs] * d[mid - l + 1] % mod) % mod;
}

void build(int l = 1, int r = n, int x = 1) {
    if(l == r) {
        seg[x] = rseg[x] = (s[l - 1] - 'a' + 1);
        return;
    }
    build(l, mid, ls); build(mid+1, r, rs);
    up(x, l, r);
}

void modify(int pos, int v, int l = 1, int r = n, int x = 1) {
    if(l == r) {
        seg[x] = rseg[x] = v;
        return;
    }
    if(pos <= mid) modify(pos, v, l, mid, ls);
    else modify(pos, v, mid+1, r, rs);
    up(x, l, r);
}

int query(int a, int b, int l = 1, int r = n, int x = 1) {
    if(a <= l and r <= b) 	return seg[x];
    int la = 0, ra = 0;
    if(a <= mid) la = query(a, b, l, mid, ls);
    if(b > mid) ra = query(a, b, mid+1, r, rs);
    if(la == 0 or ra == 0) return la | ra;
    return (la * d[min(b, r) - mid] % mod + ra) % mod;
}

int requery(int a, int b, int l = 1, int r = n, int x = 1) {
    if(a <= l and r <= b) return rseg[x];
    int la = 0, ra = 0;
    if(b > mid) ra = requery(a, b, mid + 1, r, rs);
    if(a <= mid) la = requery(a, b, l, mid, ls);
    if(la == 0 or ra == 0) return la | ra;
    return (ra * d[mid - max(l, a) + 1] % mod + la) % mod;
}

signed main() {
    IO;
    cin >> n >> m >> s;
    d[0] = 1;
    for(int i = 1; i <= n; i++) d[i] = (d[i-1] * p) % mod;
    build();
    while(m--) {
        int o, x, y;
        char c;
        cin >> o >> x;
        if(o == 1) {
            cin >> c;
            modify(x, c - 'a' + 1);
        } else {
            cin >> y;
            if(query(x, y) == requery(x, y)) cout << "Yes\n";
            else cout << "No\n";
        }
    }
}
