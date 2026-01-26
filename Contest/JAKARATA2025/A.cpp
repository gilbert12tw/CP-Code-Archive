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
    vector<int> a(n);
    for (int &i : a) cin >> i;

    int g = a[0];
    for (int i = 1; i < n; i++) {
        g = __gcd(g, a[i]);
    }
    
    if (g == 1) { // 2 times
        cout << 2 << '\n';
        cout << 4 << ' ' << 2 << '\n';
        cout << 2 << ' ' << 1 << '\n';
    } else {
        cout << 1 << '\n';
        cout << g << ' ' << 1 << '\n';
    }
}

int main() {
    ios::sync_with_stdio(false), cin.tie(0);
    solve();
}
