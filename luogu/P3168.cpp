#include<bits/stdc++.h>
//#define loli
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

// persistent segment tree
int n, m;
const int mxN = 2e5 + 5;

struct Persistent_Segment_Tree {
	int ls[mxN * 30] = {}, rs[mxN * 30] = {}, seg[mxN * 30] = {}, cnt[mxN * 30] = {};
    int tot = 0;
	#define mid ((l+r)>>1)

    Persistent_Segment_Tree () {
        memset(ls, 0, sizeof(ls)); memset(rs, 0, sizeof(rs));
        memset(seg, 0, sizeof(seg)); memset(cnt, 0, sizeof(cnt));
        tot = 0;
    }

	inline void up(int id) {
		seg[id] = seg[ls[id]] + seg[rs[id]];
        cnt[id] = cnt[ls[id]] + cnt[rs[id]];
	}

	inline void copy(int id, int p) {
		ls[id] = ls[p]; rs[id] = rs[p]; 
        seg[id] = seg[p]; cnt[id] = cnt[p];
	}

	void modify(int &id, int pos, int v, int l = 1, int r = n) {
		int p = id; id = ++tot;
		if (l == r) {
            if (v > 0) {
			    seg[id] = v; cnt[id] = 1;
            } else {
                seg[id] = 0; cnt[id] = 0;
            }
			return;
		}
		copy(id, p); // copy left right child
		if (pos <= mid) modify(ls[id], pos, v, l, mid);
		else modify(rs[id], pos, v, mid + 1, r);
		up(id);
	}

    int bs(int ed, int k, int l = 1, int r = n) {
        if (l == r) return seg[ed];
        if (cnt[ls[ed]] >= k) return bs(ls[ed], k, l, mid);
        return seg[ls[ed]] + bs(rs[ed], k - cnt[ls[ed]], mid+1, r);
    }
};

vector<pii> work[mxN];

inline void solve() {
    cin >> n >> m;
    vector<pii> tmp;
    for (int i = 1; i <= n; i++) {
        int p, s, e;
        cin >> s >> e >> p;
        tmp.eb(p, i);
        work[s].eb(p, i);
        work[e].eb(-p, i);
    }
    sort(ALL(tmp));
    tmp.resize(unique(ALL(tmp)) - tmp.begin());

    Persistent_Segment_Tree seg;
    vector<int> edit(n + 1, 0);
    for (int i = 1; i <= n; i++) {
        if (!edit[i]) edit[i] = edit[i-1];
        for (auto [p, id] : work[i]) {
            if (p > 0) {
                int pos = lower_bound(ALL(tmp), mkp(p, id)) - tmp.begin() + 1;
                seg.modify(edit[i], pos, p);
            }
        }

        //test(i, seg.cnt[edit[i]], seg.seg[edit[i]]);

        if (i != n) {
            edit[i+1] = edit[i];
            for (auto [p, id] : work[i]) {
                if (p < 0) {
                    int pos = lower_bound(ALL(tmp), mkp(-p, id)) - tmp.begin() + 1;
                    seg.modify(edit[i+1], pos, -1);
                }
            }
        }
    }

    int pre = 1;
    while (m--) {
        int x, a, b, c;
        cin >> x >> a >> b >> c;
        int k = 1 + (a * pre % c + b) % c;
        pre = seg.bs(edit[x], min(k, seg.cnt[edit[x]]));
        cout << pre << '\n';
    }
}

signed main() {
	IO;	
	solve();	
}
