#include<bits/stdc++.h>
#include<ext/pb_ds/assoc_container.hpp>
#define pb emplace_back
#define all(x) x.begin(),x.end()
#define int long long
#define pii pair<int,int>
#define mid ((l+r)>>1)
using namespace std;
const int M = 1e9+7, maxn = 2e5 + 10;

int n,q,a,b,d[maxn];

struct segment{
    int prsum = 0,sum = 0,susum = 0,mx = 0;
};

segment seg[maxn*4];

segment merge(const segment &ls, const segment &rs) {
    segment t;
    t.sum = ls.sum + rs.sum;
    t.prsum = max({ls.prsum, ls.sum + rs.prsum});
    t.susum = max({rs.susum,rs.sum + ls.susum});
    t.mx = max({ls.mx, rs.mx, ls.susum + rs.prsum});
    return t;
}

void build(int l=1,int r=n,int x=1){
    if(l == r){
        seg[x] = {d[l],d[l],d[l],d[l]};
        return ;
    }
    build(l,mid,x*2);
    build(mid+1,r,x*2+1);
    seg[x] = merge(seg[x << 1], seg[(x << 1) | 1]);
}

segment query(int a, int b, int l = 1, int r = n, int x = 1) {
    if (a <= l && r <= b) {
        return seg[x];
    }

    if (a <= mid && b > mid) return merge(query(a, b, l, mid, (x << 1)), query(a, b, mid+1, r, (x << 1) | 1));
    if (a <= mid) return query(a, b, l, mid, (x << 1));
    return query(a, b, mid+1, r, (x << 1) | 1);
}

signed main(){
    ios_base::sync_with_stdio(0);cin.tie(0);
    cin >> n >> q;
    for(int i = 1; i <= n; i++)
        cin >> d[i];
    build();
    while(q--){
        int l, r;
        cin >> l >> r;
        cout << max(0ll, query(l, r).mx) << '\n';
    }
}
