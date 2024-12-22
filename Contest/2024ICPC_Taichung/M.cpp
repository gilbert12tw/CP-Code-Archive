#include <bits/stdc++.h>
using namespace std;

using ll = long long;

ll ans = 1e18;
void Prefix(vector<int> v) {
    if (is_sorted(v.begin(), v.end())) {
        ans = 0;
        return;
    }
    long long n = (ll)v.size();
    vector<int> cnt(n);
    for (auto i : v) {
        cnt[i] ++;
    }

    vector<int> prefix_sum = cnt;
    for (int i = 1; i < n; ++ i) {
        prefix_sum[i] += prefix_sum[i - 1];
    }
    cnt.assign(n, 0);

    for (auto &i : v) {
        int tmp = i;
        i = (i == 0 ? 0 : prefix_sum[i - 1]) + cnt[i];
        ++ cnt[tmp];
    }

    vector<int> pos(n);
    for (long long pre = 0, now = 0, i = 0; i < n; ++ i) {
        pos[v[i]] = 1;
        while (now < n && pos[now] == 1) {
            ++ now;
        }
        if (v[i] != i) {
            pre = i + 1;
        }
        ans = min(ans, pre * pre + (n - now) * (n - now));
    }
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    long long n;
    cin >> n;
    vector<int> v(n);
    for (auto &i : v) cin >> i;
    
    auto l = v;
    sort(l.begin(), l.end());
    for (auto &i : v) {
        i = lower_bound(l.begin(), l.end(), i) - l.begin();
    }

    Prefix(v);
    for (auto &i : v) {
        i = (int)l.size() - i - 1;
    }
    reverse(v.begin(), v.end());
    Prefix(v);

    cout << ans << "\n";
}