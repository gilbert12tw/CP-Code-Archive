#include<bits/stdc++.h>
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
#define get_bit(x, y) ((x>>y)&1LL)
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

const int N = 21;

struct Matrix {
    int n;
    vector<int> m;
    Matrix(int _n): n(_n), m(n) {}

    Matrix operator * (const Matrix &b) {
        Matrix tm(n);
        for (int i = 0; i < n; i++) {
            for (int k = 0; k < n; k++) {
                for (int j = 0; j < n; j++) {
                    tm.m[i] |= ((get_bit(m[i], k) & get_bit(b.m[k], j)) << j);
                }
            }
        }
        return tm;
    }
};

inline void solve() {
    int n, m, a, b;
    cin >> n >> m >> a >> b;
    vector<pii> seg(m);
    for (int i = 0; i < m; i++) {
       cin >> seg[i].F >> seg[i].S; 
    }
    
    Matrix good(N);
    Matrix bad(N);
    
    for (int i = 1; i < N; i++) {
        good.m[i] = (1 << (i - 1));
        bad.m[i] = (1 << (i - 1));
    }
    for (int i = a; i <= b; i++) {
        good.m[0] |= (1 << (i - 1));
    }

    vector<Matrix> pw;
    pw.eb(good);

    int bt = 0;
    bt |= 1;

    for (int i = 1; i <= 51; i++) {
        pw.eb(pw.back() * pw.back());
    }

    const int msk = (1<<N) - 1;
    auto get_pow = [&](int n, bool is_good) {
        if (!is_good) {
            bt <<= n;
            bt &= msk;
            return;
        }

        for (int i = 50; i >= 0; i--) {
            if (get_bit(n, i)) {
                int nxt = 0;
                for (int j = 0; j < N; j++) {
                    int tmp = pw[i].m[j] & bt;
                    if (tmp) nxt |= (1 << j);
                }
                bt = nxt;
            }
        }
    };

    int now = 1;
    for (auto [l, r] : seg) {
        if (now < l - 1) {
            get_pow(l - now - 1, true);
        }
        get_pow(r - l + 1, false);
        now = r;
    }
    if (now < n) { 
        get_pow(n - now, true);
    }
    cout << ((bt & 1) ? "Yes" : "No") << '\n';
}

signed main() {
	IO;	
	solve();	
}
