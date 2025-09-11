#include <bits/stdc++.h>
using namespace std;

#define int long long
#define pii pair<int, int>
#define f first
#define s second
#define vi vector<int>
#define vll vector<long long>
#define pb push_back
#define eb emplace_back
#define SZ(a) ((int)(a).size())
#define ALL(a) a.begin(), a.end()
#define IO ios_base::sync_with_stdio(0); cin.tie(0);

const int LOG_MAX = 30;

void solve() {
    int n, q;
    cin >> n >> q;
    
    vector<pii> arr(n);
    for (int i = 0; i < n; ++i) {
        cin >> arr[i].f;
        arr[i].s = i;
    }

    stable_sort(ALL(arr), [&](const pii &a, const pii &b) {
        return __lg(a.f) < __lg(b.f);
    });

    vll prefix(n);
    for (int i = 0; i < n; ++i) prefix[i] = arr[i].f;
    partial_sum(ALL(prefix), prefix.begin());

    vi lg(n + 1, -1);
    for (int i = 1; i <= n; ++i) lg[i] = lg[i >> 1] + 1;

    int lgn = lg[n] + 1;
    vector<vi> spt(lgn, vi(n));
    for (int i = 0; i < n; ++i) spt[0][i] = arr[i].f;

    for (int lay = 1; lay < lgn; ++lay) {
        for (int i = 0; i + (1 << lay - 1) < n; ++i) {
            spt[lay][i] = min(spt[lay - 1][i], spt[lay - 1][i + (1 << (lay - 1))]);
        }
    }

    auto qmin = [&](int l, int r) {
        int lay = lg[r - l];
        return min(spt[lay][l], spt[lay][r - (1 << lay)]);
    };

    vi ql(q), qr(q);
    vll ans(q, 1);
    for (int i = 0; i < q; ++i) {
        cin >> ql[i] >> qr[i];
        --ql[i]; 
    }

    vi lb(n + 1, -1);
    for (int c = 0, ptr = 0; c < LOG_MAX; ++c) {
        for (int i = 0; i <= n; ++i) {
            lb[i] = ptr;
            if (ptr < n && arr[ptr].s == i && arr[ptr].f < (2LL << c)) ++ptr;
        }
        for (int i = 0; i < q; ++i) {
            int l = lb[ql[i]], r = lb[qr[i]];
            if (l < r && ans[i] >= qmin(l, r)) {
                ans[i] += prefix[r - 1] - (l ? prefix[l - 1] : 0);
            }
        }
    }

    for (int i = 0; i < q; ++i) {
        cout << ans[i] << '\n';
    }
}

signed main() {
    IO;
    solve();
}

