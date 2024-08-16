#include<iostream>
#include<vector>
#include<string>
#include<utility>
#include<algorithm>
#include<queue>
#include<map>
#include<set>
#include<bitset>
#define loli
using namespace std;
typedef long long ll;
#define int ll
#define pii pair<int, int>
#define X first
#define Y second
#define F first
#define S second
#define SZ(a) ((int)a.size())
#define ALL(v) v.begin(), v.end()
#define pb push_back
#define push emplace
#define lb(x, v) lower_bound(ALL(x), v)
#define ub(x, v) upper_bound(ALL(x), v)
#define re(x) reverse(ALL(x))
#define uni(x) x.resize(unique(ALL(x)) - x.begin())
#define inf 1000000000
#define INF 1000000000000000000
#define mod 1000000007
#define get_bit(x, y) ((x>>y)&1)
#define mkp make_pair
#define IO ios_base::sync_with_stdio(0); cin.tie(0);
void abc() {cout << endl;}
template <typename T, typename ...U> void abc(T a, U ...b) {
    cout << a << ' ', abc(b...);
}
template <typename T> void printv(T l, T r) {
    for (; l != r; ++l) cout << *l << " \n"[l + 1 == r];
}
template <typename A, typename B> istream& operator >> (istream& o, pair<A, B> &a) {
    return o >> a.X >> a.Y;
}
template <typename A, typename B> ostream& operator << (ostream& o, pair<A, B> a) {
    return o << '(' << a.X << ", " << a.Y << ')';
}
template <typename T> ostream& operator << (ostream& o, vector<T> a) {
    bool is = false;
    if (a.empty()) return o << "{}";
    for (T i : a) {o << (is ? ' ' : '{'), is = true, o << i;}
    return o << '}';
}
#ifdef loli
#define test(args...) abc("[" + string(#args) + "]", args)
#else
#define test(args...) void(0)
#endif

signed main() {
	IO;
    int T; cin >> T;
    while (T--) {
        int d;
        string goal;
        for (int i = 0; i < 9; i++) {
            cin >> d;
            goal.pb('0' + d);
        }

        set<string> vis;
        queue<pair<string, int>> q;
        q.push(mkp("123456780", 0));
        int ok = 0;
        while (!q.empty()) {
            auto [now, step] = q.front(); q.pop();
            if (step > 14) break;
            if (now == goal) {
                cout << "You can solve it within " << step << " steps.\n";
                ok = 1;
                break;
            }
            int pos = now.find("0");
            string nxt;
            if (pos - 3 >= 0) {
                nxt = now;
                swap(nxt[pos], nxt[pos-3]);
                if (!vis.count(nxt)) {
                    vis.insert(nxt);
                    q.push(mkp(nxt, step+1));
                }
            }
            if (pos % 3 != 0) {
                nxt = now;
                swap(nxt[pos], nxt[pos-1]);
                if (!vis.count(nxt)) {
                    vis.insert(nxt);
                    q.push(mkp(nxt, step+1));
                }
            }
            if (pos % 3 != 2) {
                nxt = now;
                swap(nxt[pos], nxt[pos+1]);
                if (!vis.count(nxt)) {
                    vis.insert(nxt);
                    q.push(mkp(nxt, step+1));
                }
            }
            if (pos + 3 < 9) {
                nxt = now;
                swap(nxt[pos], nxt[pos+3]);
                if (!vis.count(nxt)) {
                    vis.insert(nxt);
                    q.push(mkp(nxt, step+1));
                }
            }
        }
        if (!ok) cout << "You'd better skip this game.\n";
    }
}
