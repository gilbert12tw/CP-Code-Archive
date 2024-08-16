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

inline void solve() {
    int n; cin >> n;
    vector<pii> a(n);
    vector<int> b(n);
    vector<int> tmpa;
    for (int i = 0; i < n; i++) {
        cin >> a[i].F; a[i].S = i;
        tmpa.eb(a[i].F);
    }
    for (int i = 0; i < n; i++) {
        cin >> b[i];
    }
    sort(ALL(a));
    sort(ALL(b));

    vector<int> ans(n, -1);
    int j = 0;
    priority_queue<int> left;
    for (int i = 0; i < n; i++) {
        while (j + 1 < n && b[j] <= a[i].F) { 
            left.push(b[j]);
            j++;
        }
        if (j < n && b[j]  > a[i].F) ans[a[i].S] = b[j++];
        if (j == n) break;
    }
    for (; j < n; j++) {
        left.push(b[j]);
    }
    for (int i = 0; i < n; i++) {
        if (ans[i] == -1) {
            ans[i] = left.top(); left.pop();
        }
    }

    for (int cc = 0; cc < 2; cc++) {
        for (int i = 0; i < n; i++) {
            vector<int> back;
            int mx = -1;
            for (int j = i + 1; j < n; j++) {
                if (ans[j] > ans[i]) {
                    if ((ans[i] <= tmpa[i]) && (ans[j] > tmpa[j]) && ans[j] > tmpa[i] && (mx == -1 || ans[j] > ans[mx])) 
                        mx = j;
                }
            }

            if (mx != -1) {
                swap(ans[i], ans[mx]);
            }

            for (int j = i + 1; j < n; j++) {
                if (ans[j] > ans[i]) {
                    back.eb(j);
                }
            }

            sort(ALL(back), [&](int x, int y) {
                    int ax, ay;
                    if (ans[x] <= tmpa[x]) ax = -1;
                    else ax = tmpa[x];
                    if (ans[y] <= tmpa[y]) ay = -1;
                    else ay = tmpa[y];
                    return ax < ay;
            });


            for (int j : back) {
                if ((tmpa[j] >= ans[j] || ans[i] > tmpa[j]) && ans[j] > ans[i]) 
                    swap(ans[j], ans[i]);
            }
        }
    }
    for (int i = 0; i < n; i++) cout << ans[i] << " \n"[i == n-1];
}

signed main() {
    IO;	
    solve();	
}


