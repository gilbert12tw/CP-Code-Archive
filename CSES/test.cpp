#include<bits/stdc++.h>
using namespace std;
#define int long long
#define ls (x<<1)
#define rs (x<<1)+1
#define mid (l+r)/2

#define debug
void abc() {cout << endl;}
template <typename T, typename ...U> void abc(T a, U ...b) {
    cout << a << ' ', abc(b...);
}
#ifdef debug
#define test(args...) abc("[" + string(#args) + "]", args)
#else
#define test(args...) void(0)
#endif


const int mxn = 1e6;
int seg[mxn], tag[mxn];
int n, q;
int a[mxn];
void up(int x){
    seg[x] = seg[ls] + seg[rs];
}
void push_tag(int l, int r, int x, int v){
    if(v>0){
        if(tag[x]<0) tag[x] -= v;
        else tag[x] += v;
        seg[x] += (r-l+1) * v;
    }
    else if(v<0){
        tag[x] = v;
        seg[x] = (r-l+1) * (-v);
    }
}
void down(int l, int r, int x){
    if(tag[x]==0 || l==r)return;
    push_tag(l, mid, ls, tag[x]);
    push_tag(mid+1, r, rs, tag[x]);
    tag[x] = 0;

}
void build(int l = 1, int r = n, int x = 1){
    if(l == r){
        seg[x] = a[l];
        return;
    }
    build(l, mid, ls);
    build(mid+1, r, rs);
    up(x);
}

void modify(int ll, int rr, int l, int r, int x, int v){
    if(l != r)down(l, r, x);
    if(ll<=l&&r<=rr){
        push_tag(l, r, x, v);
        return;
    }
    if(ll<=mid) modify(ll, rr, l, mid, ls, v);
    if(rr>mid) modify(ll, rr, mid+1, r, rs, v);
    up(x);
}

int query(int ll, int rr, int l, int r, int x = 1){
    if(l != r)down(l, r, x);
    test(l, r, x, seg[x], tag[x]);
    if(ll<=l&&r<=rr){
        return seg[x];
    }
    int res = 0;
    if(ll<=mid) res+=query(ll, rr, l, mid, ls);
    if(rr>mid) res+=query(ll, rr, mid+1, r, rs);
    return res;
}
signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin>>n>>q;
    for(int i=1;i<=n;i++){
        cin>>a[i];
    }
    build();
    for(int i=0;i<q;i++){
        int cmd, c1, c2, c3;
        cin>>cmd;
        if(cmd == 1){
            cin>>c1>>c2>>c3;
            modify(c1, c2, 1, n, 1, c3);
            test(tag[1], seg[1]);
        }
        if(cmd == 2){
            cin>>c1>>c2>>c3;
            modify(c1, c2, 1, n, 1, -c3);
        }
        if(cmd == 3){
            cin>>c1>>c2;
            cout<<query(c1, c2, 1, n, 1)<<'\n';
        }
    }
}

