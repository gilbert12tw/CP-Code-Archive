#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

vector<ll> parseList(string s) {
    vector<ll> ans;
    ll res = 0;
    for (int i = 1; i < s.size() - 1; i++) {
        if (!isdigit(s[i])) {
            ans.push_back(res);
            res = 0;
            continue;
        }
        res = res * 10LL + (s[i] - '0');
    }
    ans.push_back(res);
    return ans;
}

int main() {
    ios::sync_with_stdio(false), cin.tie(0);

    string tmp;
    getline(cin, tmp);
    auto l = parseList(tmp);
    getline(cin, tmp);
    auto r = parseList(tmp);
    getline(cin, tmp);
    auto v = parseList(tmp);

    int n = v.size();
    vector<array<ll, 3>> items;
    for (int i = 0; i < n; i++) {
        //cout << l[i] << ", " << r[i] << ", " << v[i] << '\n';
        items.push_back({l[i], r[i], v[i]});
    }
    
    sort(items.begin(), items.end(), [&](array<ll, 3> a, array<ll, 3> b) {
        return a[1] < b[1];
    });
    map<ll, ll> mp;
    mp[0] = 0;
    
    for (int i = 0; i < n; i++) {
        auto it = mp.upper_bound(items[i][0]);
        it = prev(it);

        ll tmx = (*mp.rbegin()).second;
        mp[items[i][1]] = max(mp[items[i][1]], (*it).second + items[i][2]);
        mp[items[i][1]] = max(mp[items[i][1]], tmx);
    }
    
    ll ans = 0;
    for (auto [l, v] : mp) ans = max(ans, v);
    cout << ans << '\n';
}
