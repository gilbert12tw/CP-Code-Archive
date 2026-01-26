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