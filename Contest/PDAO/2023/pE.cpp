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

int n, d;
vector<int> player[2];

int check(int x) {
    for (int i = 1; i < SZ(player[0]); i++) {

    }
    return 1;
}

inline void solve() {
    cin >> n >> d;
    int odd = 0;
    player[0].clear();
    player[1].clear();

    player[0].eb(0);
    player[1].eb(0);
    player[0].eb(d);
    player[1].eb(d);

    vector<pii> v;
    for (int i = 0; i < n; i++) {
        int x; char c; 
        cin >> c >> x;
        v.eb(x, c == 'R');
    }
    sort(ALL(v));


    for (int i = 0; i < n; i++) {
        char c = 'I';
        if (v[i].S) c = 'R';
        int x = v[i].F;

        if (c == 'R') {
            player[0].eb(x);
            player[1].eb(x);
        }
        else { 
            player[odd].eb(x);
        }
        odd ^= 1;
    }
    sort(ALL(player[0]));
    sort(ALL(player[1]));

    int ans = -1;
    for (int i = 1; i < SZ(player[0]); i++) {
        ans = max(ans, player[0][i] - player[0][i-1]);
    }

    for (int i = 1; i < SZ(player[1]); i++) {
        ans = max(ans, player[1][i] - player[1][i-1]);
    }
    cout << ans << '\n';
}

signed main() {
	IO;	
    int T; cin >> T;
	while (T--) solve();	
}
