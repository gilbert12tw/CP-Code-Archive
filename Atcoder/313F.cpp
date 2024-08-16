#include<bits/stdc++.h>
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
#define get_bit(x, y) ((x>>y)&1LL)
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

inline void solve() {
    int n, m;
    cin >> n >> m;
    vector<int> d(n);
    int sum = 0;
    for (int i = 0; i < n; i++) {
        int a, b;
        cin >> a >> b;
        d[i] = (b - a);
        sum += a;
    }

    vector<pii> machine;
    for (int i = 0; i < m; i++) {
        int x, y; 
        cin >> x >> y;
        x--, y--;
        if (x == y) {
            if (d[x] >= 0) {
                sum += d[x];
                d[x] = -d[x]; 
            }
            continue;
        } 
        machine.eb(x, y);
    }
    m = SZ(machine);

    vector<int> chosen(n);
    vector<pii> tmp;
    for (auto [x, y] : machine) {
        if (d[x] < 0 && d[y] < 0)
            continue;

        if (d[x] >= 0 && d[y] >= 0) {
            chosen[x] = chosen[y] = 1;
        } else {
            tmp.eb(x, y);
        }
    }
    machine = tmp;

    int pcnt = 0;
    for (int i = 0; i < n; i++) 
        pcnt += (d[i] < 0);

    auto sol1 = [&]() {
        vector<int> ord(n);
        iota(ALL(ord), 0);
        sort(ALL(ord), [&](int a, int b) {
            return d[a] < d[b];
        });

        vector<int> b(n);
        for (auto [x, y] : machine) {
            if (d[x] >= 0) 
                swap(x, y);
            assert(d[x] < 0);
            b[x] = (b[x] | (1LL<<y));
        }
        int msk = 0;
        for (int i = 0; i < n; i++) {
            if (chosen[i]) 
                msk |= (1LL<<i);
        }

        int ans = 0;
        for (int i = 0; i < (1<<pcnt); i++) {
            int res = msk;
            int cost = 0;
            for (int j = 0; j < pcnt; j++) {
                if (get_bit(i, j)) {
                    res |= b[ord[j]];
                    cost += d[ord[j]];
                }
            }
            for (int j = 0; j < n; j++) {
                if (get_bit(res, j)) {
                    assert(d[j] >= 0);
                    cost += d[j];
                }
            }
            ans = max(ans, cost);
        }
        return ans;
    };

    auto sol2 = [&]() {
        int qcnt = n - pcnt;
        vector<int> ord(n);
        iota(ALL(ord), 0);
        sort(ALL(ord), [&](int a, int b) {
            return d[a] > d[b];
        });
        vector<int> rk(n);
        for (int i = 0; i < n; i++) rk[ord[i]] = i;

        vector<int> b(n);
        for (auto [x, y] : machine) {
            if (d[x] >= 0) 
                swap(x, y);
            assert(d[x] < 0);
            b[rk[x]] = (b[rk[x]] | (1<<rk[y]));
        }

        vector<int> dp((1<<qcnt), -INF);
        int msk = 0;
        for (int i = 0; i < n; i++) {
            if (chosen[i]) 
                msk |= (1<<rk[i]);
        }
        dp[msk] = 0;

        for (int i = qcnt; i < n; i++) {
            test(i, b[i], d[ord[i]]);
            for (int j = 0; j < (1<<qcnt); j++) {
                int bsk = j | b[i];
                dp[bsk] = max(dp[bsk], dp[j] + d[ord[i]]);
            }
        }

        int ans = 0;
        for (int i = 0; i < (1<<qcnt); i++) {
            int res = dp[i];
            for (int j = 0; j < qcnt; j++) {
                if (get_bit(i, j)) {
                    assert(d[ord[j]] >= 0);
                    res += d[ord[j]];
                }
            }
            ans = max(ans, res);
        }
        return ans;
    };

    int out = 0;
    if (pcnt <= 20) {
        out = sol1();
    } else {
        out = sol2();
    }
    cout << sum + out / 2;
    if (out % 2) cout << ".5\n";
}

signed main() {
	IO;	
	solve();	
}
