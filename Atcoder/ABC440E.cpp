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

struct Node {
    ll val;
    int id, cur, lim;
    bool operator < (const Node& other) const {
        return val < other.val;
    };
};

void solve() {
    int n, k, x;
    cin >> n >> k >> x;
    
    vector<ll> a(n), diff(n);
    for (auto &i : a) cin >> i;
    sort(ALL(a));
    reverse(ALL(a));
    for (int i = 0; i < n - 1; i++) {
        diff[i] = a[i] - a[i+1];
    }

    if (n == 1) {
        cout << a[0] * k << '\n';
        return;
    }

    priority_queue<Node> pq;
    // init
    pq.push({a[0] * k, 0, 0, k});

    for (int _ = 0; _ < x; _++) {
        auto u = pq.top(); pq.pop();
        cout << u.val << '\n';

        if (u.cur < u.lim) {
            auto nxt = u;
            nxt.cur++;
            nxt.val -= diff[u.id];
            pq.push(move(nxt));
        }
        if (u.cur > 0 && u.id + 1 < n - 1) {
            auto nxt = u;
            nxt.cur = 1;
            nxt.val -= diff[u.id + 1];
            nxt.id = u.id + 1;
            nxt.lim = u.cur;
            pq.push(move(nxt));
        }
    }
}

int main() {
    ios::sync_with_stdio(false), cin.tie(0);
    solve();
}
