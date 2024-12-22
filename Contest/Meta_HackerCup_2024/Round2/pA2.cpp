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

#define ull unsigned long long
vector<ull> peaks;

inline void solve(int cs) {
    ull a, b, m;
    cin >> a >> b >> m;
    int st = lower_bound(ALL(peaks), a) - peaks.begin() - 1;
    if (st < 0) st = 0;

    ull ans = 0;
    if (m == 1) {
        ans = upper_bound(ALL(peaks), b) - lower_bound(ALL(peaks), a);
    } else {
        for (int i = st; i < SZ(peaks) ; i++) {
            if (peaks[i] > b) break;
            if (peaks[i] < a) continue;
            if (peaks[i] % m == 0) ans++;
        }
    }

    cout << "Case #" << cs << ": ";
    cout << ans << '\n';
}

signed main() {
    IO;	

    auto gen_peaks = []() {
        vector<vector<int>> pre(10);
        vector<int> p10(15);
        p10[0] = 1;
        for (int i = 1; i <= 10; i++) p10[i] = p10[i-1] * 10;

        auto rev = [](int x) -> int {
            int res = 0;
            while (x) {
                res = res * 10 + x % 10;
                x /= 10;
            }
            return res;
        };

        for (int mid = 0; mid <= 9; mid++) {
            if (mid == 0) {
                pre[0].eb(0);
                continue;
            }
            if (mid == 1) {
                peaks.eb(mid);
                continue;
            }
            peaks.eb(mid);

            for (int i = 1; i <= 8; i++) {
                for (int j : pre[i-1]) {
                    if (j % 10 <= mid - 1) {
                        pre[i].eb(j * 10ULL + (mid - 1));
                    }
                }
            }

            for (int i = 1; i <= 8; i++) {
                for (int j : pre[i]) {
                    for (int k : pre[i]) {
                        int rk = rev(k);
                        if ((j % 10 < mid) && (k % 10 < mid)) {
                            peaks.eb(j * p10[i + 1] + mid * p10[i] + rk);
                        }
                    }
                }
            }
        }

        sort(peaks.begin(), peaks.end());
    };

    gen_peaks();

    //for (int i = 0; i < 500; i++) test(peaks[i]);

    int T; cin >> T;
    for (int i = 1; i <= T; i++) solve(i);	
}
