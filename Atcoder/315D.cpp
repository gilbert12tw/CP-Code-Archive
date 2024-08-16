#include<bits/stdc++.h>
#define loli
using namespace std;
typedef long long ll;
#pragma GCC optimize("Ofast,unroll-loops")
#pragma loop-opt(on)
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,avx,avx2,fma,tune=native")
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

char mat[2001][2001];
int n, m;
int cr[2001], cc[2001];

inline void solve() {
    cin >> n >> m;
    for (int i = 0; i < n; i++) {
        cin >> mat[i];
    }
    
    queue<pii> q;

    int cntr = 0, cntc = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 1; j < m; j++) {
            if (mat[i][j] != mat[i][j-1]) cr[i]++;
        }
        if (cr[i] == 0) {
            q.push(i, 0);
            cntr++;
        }
    }

    for (int i = 0; i < m; i++) {
        for (int j = 1; j < n; j++) {
            if (mat[j][i] != mat[j-1][i]) cc[i]++;
        }
        if (cc[i] == 0) {
            q.push(i, 1);
            cntc++;
        }
    }
    
    while (!q.empty()) {
        auto [a, tp] = q.front(); q.pop();
        if (tp) {
            if (cntc == m - 1) continue;
            for (int j = 0; j < n; j++) {
                int p = cr[j];
                if (a && mat[j][a] != mat[j][a-1] && cr[a-1]) cr[j]--;
                if (a != m - 1 && mat[j][a] != mat[j][a+1] && cr[a+1]) cr[j]--;

                if (p && cr[j] == 0) {
                    q.push(j, 0);
                    cntr++;
                }
            }
        } else {
            if (cntr == n - 1) continue;
            for (int j = 0; j < m; j++) {
                int p = cc[j];
                if (a && mat[a][j] != mat[a-1][j] && cc[a-1]) cc[j]--;
                if (a != n - 1 && mat[a][j] != mat[a+1][j] && cc[a+1]) cc[j]--;
                if (p && cc[j] == 0) {
                    q.push(j, 1);
                    cntc++;
                }
            }
        }
    }
    int ans = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (cr[i] != 0 && cc[j] != 0) ans++;
        }
    }
    cout << ans;
}

signed main() {
	IO;	
	solve();	
}
