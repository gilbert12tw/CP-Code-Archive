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

inline void solve() {
    int n; cin >> n;
    vector<int> a(n);
    for (int &i : a) cin >> i;

    vector<set<pii>> index_order, val_order;

    set<pii> tmp_i;
    set<pii> tmp_v;
    for (int i = 1; i <= n; i++) {
        tmp_i.insert(mkp(i, a[i-1]));
        tmp_v.insert(mkp(a[i-1], i));
    }
    index_order.eb(tmp_i);
    val_order.eb(tmp_v);

    int q; cin >> q;
    for (int i = 1; i <= q; i++) {
        int t, s, x;
        cin >> t >> s >> x;
        auto &st_index = index_order[s];
        auto &st_val = val_order[s];
        int lsz = SZ(st_index);

        set<pii> newst_i, newst_v;

        if (st_val.empty()) {
            index_order.eb(newst_i);
            val_order.eb(newst_v);
            cout << 0 << '\n';
            continue;
        }

        if (t == 1) {
            if (lsz - x <= x) { 
                if (lsz - x > 0) {
                    auto it = prev(st_index.end(), lsz - x);
                    while (it != st_index.end()) {
                        st_val.erase(mkp(it->S, it->F));
                        newst_i.insert(mkp(it->F, it->S));
                        newst_v.insert(mkp(it->S, it->F));
                        it = st_index.erase(it);
                    }
                }
                index_order.eb(newst_i);
                val_order.eb(newst_v);
            } else {
                int rcnt = 0;
                auto it = st_index.begin();
                while (it != st_index.end()) {
                    if (rcnt++ >= x) break;
                    st_val.erase(mkp(it->S, it->F));
                    newst_i.insert(mkp(it->F, it->S));
                    newst_v.insert(mkp(it->S, it->F));
                    it = st_index.erase(it);
                }
                index_order.eb(newst_i);
                val_order.eb(newst_v);
                swap(index_order[i], index_order[s]);
                swap(val_order[i], val_order[s]);
            }
        } else {
            int type = 1;
            auto hd = st_val.begin(), ed = prev(st_val.end());
            if (hd->F > x) {
                type = 1;
            } else if (ed->F <= x) { 
                type = 0;
            } else {
                while (1) {
                    if (hd->F > x) {
                        type = 1;
                        break;
                    }
                    if (ed->F <= x) {
                        type = 0;
                        break;
                    }
                    if (hd == prev(st_val.end()) || ed == st_val.begin())
                        break;
                    hd = next(hd);
                    ed = prev(ed);
                }
            }

            if (type == 0) {
                auto it = st_val.upper_bound(mkp(x, INF));
                while (it != st_val.end()) {
                    st_index.erase(mkp(it->S, it->F));
                    newst_v.insert(mkp(it->F, it->S));
                    newst_i.insert(mkp(it->S, it->F));
                    it = st_val.erase(it);
                }
                index_order.eb(newst_i);
                val_order.eb(newst_v);
            } else {
                auto it = st_val.begin();
                while (it != st_val.end()) {
                    if (it->F > x) break;
                    st_index.erase(mkp(it->S, it->F));
                    newst_v.insert(mkp(it->F, it->S));
                    newst_i.insert(mkp(it->S, it->F));
                    it = st_val.erase(it);
                }
                index_order.eb(newst_i);
                val_order.eb(newst_v);
                swap(index_order[i], index_order[s]);
                swap(val_order[i], val_order[s]);
            }
        }
        cout << SZ(index_order[i]) << endl;
    }
}

signed main() {
    IO;	
    solve();	
}
