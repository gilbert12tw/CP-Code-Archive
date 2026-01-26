#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

void solve() {
    string s;
    cin >> s;
    string ans;
    for (int i = 0; i < s.size(); i++) {
        int cnt = 1;
        while (i + 1 < s.size() && s[i + 1] == s[i]) {
            cnt++;
            i++;
        }
        ans.push_back(s[i]);
        if (cnt > 1) {
            ans += to_string(cnt);
        }
    }
    cout << ans << '\n';
}

int main() {
    ios::sync_with_stdio(false), cin.tie(0);
    solve();
}
