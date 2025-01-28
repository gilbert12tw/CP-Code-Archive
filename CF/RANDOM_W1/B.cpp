#include<bits/stdc++.h>
#pragma GCC optimize("Ofast,unroll-loops")
#pragma loop-opt(on)
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,avx,avx2,fma,tune=native")
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
void abc() {cerr << endl;}
template <typename T, typename ...U> void abc(T a, U ...b) {
    cerr << a << ' ', abc(b...);
}
#ifdef debug
#define test(args...) abc("[" + string(#args) + "]", args)
#else
#define test(args...) void(0)
#endif

template<class T> bool ckmin(T& a, const T& b) { return b<a ? a=b, 1 : 0; }
template<class T> bool ckmax(T& a, const T& b) { return a<b ? a=b, 1 : 0; }

const int mxN = 2e5 + 5;
#define next(x) link[x].nxt
#define prev(x) link[x].lst
struct Node {
    int val, cnt;
    int nxt, lst;
    Node (int _v, int _c): val(_v), cnt(_c), nxt(0), lst(0) {}
    Node (): val(-1), cnt(-1), nxt(0), lst(0) {}
} link[mxN];
set<pii> st;

int tot = 0;
int newNode(int v, int c) {
    link[++tot] = Node(v, c);
    return tot;
}

void del(int u) {
    st.erase(mkp(-link[u].cnt, u));
    if (prev(u) != 0) next(prev(u)) = next(u);
    if (next(u) != 0) prev(next(u)) = prev(u);
}

void merge(int u) {
    if (st.find(mkp(-link[u].cnt, u)) == st.end()) {
        return;
    }
    st.erase(mkp(-link[u].cnt, u));
    if (next(u) != 0 && link[u].val == link[next(u)].val) {
        test(next(u));
        link[u].cnt += link[next(u)].cnt;
        del(next(u));
    }
    if (prev(u) != 0 && link[u].val == link[prev(u)].val) {
        link[u].cnt += link[prev(u)].cnt;
        del(prev(u));
    }
    st.insert(mkp(-link[u].cnt, u));
}

inline void solve() {
    int n; cin >> n;
    vector<int> a(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }

    for (int i = 1; i <= n; i++) {
        int j = i;
        while (j + 1 <= n && a[j + 1] == a[i]) {
            j++;
        }
        int cnt = j - i + 1;
        int id = newNode(a[i], cnt);
        st.insert(mkp(-cnt, id));
        i = j;
    }

    for (int i = 1; i <= tot; i++) {
        if (i != 1) link[i].lst = i - 1;
        if (i != tot) link[i].nxt = i + 1;
    }

    int rd = 0;
    while (SZ(st) > 0 && rd < n) {
        auto [len, id] = *st.begin();
        len = -len;
        test(len, id);
        int lst = prev(id);
        int nxt = next(id);
        //test(link[id].val, link[lst].val, link[nxt].val);
        del(id);
        if (lst) merge(lst);
        if (nxt) merge(nxt);
        rd++;
    }
    cout << rd << '\n';
}

signed main() {
	IO;	
	solve();	
}
