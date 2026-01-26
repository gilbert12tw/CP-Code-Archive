#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n; cin >> n;
    vector<string> s(n);
    for (int i = 0; i < n; i++) cin >> s[i];

    #define node tuple<string, int, int>
    map<node, int> mp;

    int ans = 0;
    auto check = [](string a, string b) -> int {
        int diff = 0;
        int n = a.size(); 
        int m = b.size();
        if (n != m) return -1;
        for (int i = 0; i < n; i++) {
            if (a[i] != b[i]) diff++;
        }
        if (diff != 2) return -1;
        for (int i = 0; i < n - 1; i++) {
            if (a[i] != b[i] && a[i+1] != b[i+1]) {
                return i;
            }
        }
        return -1;
    };
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            int pos = check(s[i], s[j]);
            if (pos == -1) continue;
            string tmp_a, tmp_b;
            tmp_a.push_back(s[i][pos]);
            tmp_a.push_back(s[i][pos + 1]);
            tmp_b.push_back(s[j][pos]);
            tmp_b.push_back(s[j][pos + 1]);
            int len = s[i].size();

            auto tmp = make_tuple(min(tmp_a, tmp_b) + max(tmp_a, tmp_b), pos, len);
            mp[tmp]++;
        }
    }
    for (auto [nod, val] : mp) {
        if (val == 1) {
            ans++;
        }
    }
    cout << ans << '\n';
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    solve();
}
