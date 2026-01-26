#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

void solve() {
    int x;
    unordered_set<int> s;
    vector<int> a;
    while (cin >> x) {
        if (s.find(x) != s.end()) 
            continue;
        s.insert(x);
        a.push_back(x);
    }

    for (int i = 0; i < a.size(); i++) 
        cout << a[i] << " \n"[i == a.size() - 1];
}

int main() {
    ios::sync_with_stdio(false), cin.tie(0);
    solve();
}
