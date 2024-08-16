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
#define mod 998244353
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

int dis2(pii a, pii b) {
    return (a.X - b.X) * (a.X - b.X) + (a.Y - b.Y) * (a.Y - b.Y);
}

int cross(pii a, pii b) {
    return a.X * b.Y - a.Y * b.X;
}

pii sub(pii a, pii b) {
    return mkp(a.X - b.X, a.Y - b.Y);
}

inline void solve() {
    int n;
    cin >> n;
    vector<int> p2(n + 1, 1);
    for (int i = 1; i <= n; i++) p2[i] = (p2[i-1] << 1) % mod;

    vector<pii> pt(n);
    for (auto &i : pt) cin >> i;

    int ans = p2[n] - n - 1;
    for (int i = 0; i < n; i++) {
        for (int j = i+1; j < n; j++) {
            int cnt = 0;
            for (int k = j+1; k < n; k++) {
                if (cross(sub(pt[i], pt[j]), sub(pt[k], pt[j])) == 0) {
                    cnt++;
                }
            }
            ans = (ans - p2[cnt]) % mod;
            if (ans < 0) ans += mod;
        }
    }
        
    cout << ans;
}

signed main() {
	IO;	
	solve();	
}
