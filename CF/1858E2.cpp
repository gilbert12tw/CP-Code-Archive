#include<bits/stdc++.h>
//#define loli
using namespace std;
typedef long long ll;
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

#pragma GCC optimize("Ofast,unroll-loops")
#pragma loop-opt(on)
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,avx,avx2,fma,tune=native")

template<class T> bool ckmin(T& a, const T& b) { return b<a ? a=b, 1 : 0; }
template<class T> bool ckmax(T& a, const T& b) { return a<b ? a=b, 1 : 0; }


const int mxN = 1e6 + 5;
// persistent segment tree
struct persistent_segment {
	int ls[mxN * 22] = {}, rs[mxN * 22] = {}, seg[mxN * 22] = {}, sum[mxN * 22] = {}, tot = 0;
	#define mid ((l+r)>>1)
	inline void up(int id) {
		sum[id] = sum[ls[id]] + sum[rs[id]];
	}
	inline void copy(int id, int p) {
		ls[id] = ls[p]; rs[id] = rs[p]; seg[id] = seg[p]; sum[id] = sum[p];
	}
    inline int new_copy(int x) {
        ++tot;
        copy(tot, x);
        return tot;
    }
	void modify(int &id, int pos, int v, int l = 1, int r = 1000000) {
		int p = id;
		id = ++tot;
		if (l == r) {
			seg[id] += v;
            if (seg[id] > 0) sum[id] = 1;
            else sum[id] = 0;
			return;
		}
		copy(id, p); 
		if (pos <= mid) modify(ls[id], pos, v, l, mid);
		else modify(rs[id], pos, v, mid + 1, r);
		up(id);
	}
} perseg;

inline void solve() {
    int q; cin >> q;
    vector<int> edit(q + 1), last_pos(q + 1), pos(q + 1);
    vector<vector<int>> pa(21, vector<int>(q + 1, 0));

    int tot = 0;
    for (int i = 1; i <= q; i++) {
        char c; cin >> c;
        if (c == '+') {
            int x; cin >> x;
            int nw = perseg.new_copy(edit[tot]);
            edit[++tot] = nw;
            perseg.modify(edit[tot], x, 1);
            pos[tot] = tot;
            pa[0][pos[tot]] = pos[tot-1];
            for (int j = 1; j <= 20; j++)
                pa[j][pos[tot]] = pa[j-1][pa[j-1][pos[tot]]];
            last_pos[tot] = pos[tot-1];
        } else if (c == '-') {
            int k; cin >> k;
            int u = pos[tot];
            last_pos[++tot] = u;
            for (int j = 20; j >= 0; j--) 
                if (get_bit(k, j))
                   u = pa[j][u]; 
            pos[tot] = u;
            edit[tot] = edit[u];
        } else if (c == '!') {
            ++tot;
            pos[tot] = last_pos[tot-1];
            last_pos[tot] = last_pos[pos[tot]];
            edit[tot] = edit[pos[tot]];
        } else if (c == '?') {
            cout << perseg.sum[edit[tot]] << endl;
        }
        test(c, pos[tot], perseg.sum[edit[tot]]);
    }

}

signed main() {
	IO;	
	solve();	
}
