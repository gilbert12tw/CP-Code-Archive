#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> pii;
#define eb emplace_back
#define ALL(a) a.begin(), a.end()
#define SZ(a) ((int)a.size())

#ifdef debug
template <typename T>
ostream& operator << (ostream &o, vector<T> vec) {
    o << "{"; int f = 0; for (T i : vec) o << (f++ ? " " : "") << i; return o << "}";
}
void bug__(int c, auto ...a) {
    cerr << "\e[1;" << c << "m"; (..., (cerr << a << " ")); cerr << "\e[0m" << endl;
}
#define bug_(c, x...) bug__(c, __LINE__, "[" + string(#x) + "]", x)
#define bug(x...) bug_(32, x)
#define bugv(x...) bug_(36, vector(x))
#else
#define bug(x...) void(0)
#define bugv(x...) void(0)
#endif

void solve() {
    int n; cin >> n;

    const int inf = 30000;
    vector<vector<int>> passed(20, vector<int>(430, inf));
    vector<int> cnt(430);
    vector<array<int, 3>> sb;

    for (int i = 0; i < n; i++) {
        int a, b, c;
        cin >> a >> b >> c;
        sb.push_back({a, b, c});
        if (passed[b][a] <= c) continue;
        if (c < 240) { 
            passed[b][a] = c;
            cnt[a]++;
        } else {
            if (cnt[a] < 3) {
                passed[b][a] = c;
                cnt[a]++;
            }
        }
    }
    
    for (int i = 0; i < n; i++) {
        int a = sb[i][0];
        int b = sb[i][1];
        int c = sb[i][2];
        if (passed[b][a] == c) {
            passed[b][a] = -1;
            cout << b << '\n';
        } else {
            cout << 0 << '\n';
        }
    }
}

int main() {
    ios::sync_with_stdio(false), cin.tie(0);
    solve();
}
