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
#define get_bit(x, y) ((x>>y)&1)
#define mkp make_pair
#define IO ios_base::sync_with_stdio(0); cin.tie(0);
void abc() {cout << endl;}
template <typename T, typename ...U> void abc(T a, U ...b) {
    cout << a << ' ', abc(b...);
}
template <typename T> void printv(T l, T r) {
    for (; l != r; ++l) cout << *l << " \n"[l + 1 == r];
}
template <typename A, typename B> istream& operator >> (istream& o, pair<A, B> &a) {
    return o >> a.X >> a.Y;
}
template <typename A, typename B> ostream& operator << (ostream& o, pair<A, B> a) {
    return o << '(' << a.X << ", " << a.Y << ')';
}
template <typename T> ostream& operator << (ostream& o, vector<T> a) {
    bool is = false;
    if (a.empty()) return o << "{}";
    for (T i : a) {o << (is ? ' ' : '{'), is = true, o << i;}
    return o << '}';
}
#ifdef loli
#define test(args...) abc("[" + string(#args) + "]", args)
#else
#define test(args...) void(0)
#endif

const int mxN = 2e6 + 5;

int n, q;

int trie[10000000 + 5][2], tot;
int mx[10000000 + 5];

void insert(int x, int val) {
    int cur = 0;
    for (int i = 22; i >= 0; i--) {
        int &go = trie[cur][get_bit(x, i)];
        if (!go) go = ++tot;
        mx[go] = max(mx[go], val);
        cur = go;
    }
}

int query(int m, int k) {
    int cur = 0, res = 0;
    for (int i = 22; i >= 0; i--) {
        int mi = get_bit(m, i);
        int ki = get_bit(k, i);
        if (mi && ki) {
            res = max(mx[trie[cur][1]], res);
            cur = trie[cur][0];
        } else if (!mi && ki) {
            res = max(mx[trie[cur][0]], res);
            cur = trie[cur][1];
        } else if (mi && !ki) {
            cur = trie[cur][1];
        } else {
            cur = trie[cur][0];
        }
        if (!cur) break; 
    }
    if (cur) res = max(res, mx[cur]);
    return res;
}

inline void solve() {
    cin >> n >> q;
    for (int i = 0; i < n; i++) {
        int a; cin >> a;        
        insert(i, a);
    }

    while (q--) {
        int m, k;
        cin >> m >> k;
        cout << query(m, k) << '\n';
    }

}

signed main() {
	IO;	
	solve();	
}
