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
#define mod 1000000007TTIVATTI<F9>kiTTIVATTIkkkk
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

inline void solve() {
    string s;
    cin >> s;
    vector<int> cnt(30);
    for (char c : s) cnt[c - 'A']++;

    string ans;
    int n = SZ(s), p = -1;

    for (int i = n; i >= 1; i--) {
        int mx_id = -1, secmx_id = -1, sm_id = -1;
        for (int j = 0; j < 26; j++) {
            if (j == p) continue;
            if (mx_id == -1 || cnt[j] > cnt[mx_id]) {
                secmx_id = mx_id;
                mx_id = j;
            }
            else if (secmx_id == -1 || cnt[j] > cnt[secmx_id]) {
                secmx_id = j;
            }
            if (sm_id == -1 && cnt[j] > 0) sm_id = j;
        }
        if (mx_id != -1 && cnt[mx_id] * 2 > i) {
            ans.push_back('A' + mx_id);
            cnt[mx_id]--;
        } else if (mx_id != -1 && secmx_id != -1 && cnt[mx_id] * 2 == i && cnt[secmx_id] * 2 == i) {
            ans.push_back('A' + mx_id);
            cnt[mx_id]--;
        } else {
            if (sm_id == -1) {
                test(ans);
                cout << -1 << '\n';
                return;
            }
            ans.push_back('A' + sm_id);
            cnt[sm_id]--;
        }
        p = ans.back() - 'A';
    }

    cout << ans << '\n';
}

signed main() {
	IO;	
	solve();	
}
