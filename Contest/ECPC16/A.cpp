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
    int g, n, k;
    cin >> g;
    int nim_sum = 0;
    for (int i = 0; i < g; i++) {
        cin >> k >> n;
        if (k & 1) {
            nim_sum ^= (n & 1);
        } else {
            if (n % (k + 1) == k) {
                nim_sum ^= 2;
            } else {
                nim_sum ^= ((n % (k + 1)) & 1);
            }
        }
    }
    if (nim_sum) cout << 1 << '\n';
    else cout << 2 << '\n';


    /*
    cin >> k >> n;
    vector<int> sg(n + 1);

    for (int i = 1; i <= n; i++) {
        int mul = 1;
        vector<int> tmp;
        while (mul <= i) {
            tmp.eb(sg[i - mul]);
            mul *= k;
        }
        sort(ALL(tmp));
        tmp.resize(unique(ALL(tmp)) - tmp.begin());
        // mex
        for (int j = 0; ; j++) {
            if (tmp[j] != j) {
                sg[i] = j;
                break;
            }
        }
    }
    
    for (int i = 1; i <= n; i++) {
        bug(i, sg[i]);
    }
    */
}

inline void setIO(string name) {
    ios_base::sync_with_stdio(0); cin.tie(0);
    freopen((name+".in").c_str(),"r",stdin);
}

int main() {
    ios::sync_with_stdio(false), cin.tie(0);
    //setIO("powers");
    int T; cin >> T;
    while (T--) solve();
}
