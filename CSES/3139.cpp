#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
#define int ll
#define pii pair<int, int>
#define f first
#define s second
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


mt19937 gen(chrono::steady_clock::now().time_since_epoch().count());

inline void solve() {
    int n;
    cin >> n;
    
    auto ask = [](int i, int j) -> bool {
        cout << "? " << i+1 << ' ' << j+1 << '\n';
        cout.flush();
        string s; cin >> s;
        return (s[0] == 'Y');
    };

    vector<int> a(n), tmp(n);
    iota(ALL(a), 0);

    auto merge_sort = [&](int l, int r, auto &&merge_sort) -> void {
        if (l >= r) return;
        int mid = (l + r) >> 1;
        merge_sort(l, mid, merge_sort);
        merge_sort(mid+1, r, merge_sort);
        // merge
        int i = l, j = mid + 1, tot = l;
        while (tot <= r) {
            if (i > mid) {
                tmp[tot++] = a[j++];
            } else if (j > r) {
                tmp[tot++] = a[i++];
            } else if (ask(a[i], a[j])) {
                tmp[tot++] = a[i++];
            } else {
                tmp[tot++] = a[j++];
            }
        }
        for (int i = l; i <= r; i++) a[i] = tmp[i];
    };
    merge_sort(0, n - 1, merge_sort);

    vector<int> mp(n);
    for (int i = 0; i < n; i++) {
        mp[a[i]] = i;
    }
    cout << "! "; for (int i : mp) cout << i+1 << ' ';
}

signed main() {
	IO;	
	solve();	
}
