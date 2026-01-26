#include <bits/stdc++.h>
using namespace std;

int checksum10(string s) {
    int m = 10;
    int x = 0;
    assert(s.size() == 10);
    for(int i = 0; i < 10; i++) {
        int d = (s[i] == 'X' ? 10 : s[i] - '0');
        x += d * m;
        m--;
    }
    x %= 11;
    return x;
}

void solve() {
    string s;
    cin >> s;
    string t;
    for(char c : s) {
        if(c == '-') continue;
        t += c;
    }
    cerr << "ck = " << checksum10(t) << std::endl;
    if(checksum10(t) != 0) {
        cout << "invalid\n";
        return;
    }
    t = string("987") + t.substr(0, 9);
    int x = 0;
    for(int i = 0; i < (int) t.size(); i++) {
        x += (i % 2 == 0 ? 1 : 3) * (t[i] - '0');
    }
    x %= 10;
    cout << t << (10 - x) % 10 << "\n";
}

int main() {
    int tt;
    cin >> tt;
    while(tt--) {
        solve();
    }
}
