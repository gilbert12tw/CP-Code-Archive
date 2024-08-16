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
#define eb emplace_back
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

const int mxN = 205;

int n;
int x[mxN], l[mxN];

bool check(int k) {
    vector<int> tmp;
    for (int i = 0; i < n; i++) 
        tmp.eb(abs(x[i] - k));
    sort(ALL(tmp));
    for (int i = 0; i < n; i++) 
        if (tmp[i] > l[i]) return false;
    return true;
}

int findr(int one) {
    int l = one, r = INF;
    while (l < r) {
        int mid = l + (r - l + 1) / 2;
        if (check(mid)) l = mid;
        else r = mid - 1;
    }
    return l;
}

int findl(int one) {
    int l = -INF, r = one;
    while (l < r) {
        int mid = l + (r - l + 1) / 2;
        if (!check(mid)) l = mid;
        else r = mid - 1;
    }
    return l;
}

inline void solve() {
    cin >> n;
    for (int i = 0; i < n; i++) cin >> x[i];
    for (int i = 0; i < n; i++) cin >> l[i];
    sort(l, l + n);
    sort(x, x + n);

    int one = 0, ok = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (check(x[i] + l[j])) {
                one = x[i] + l[j];
                ok = 1;
                break;
            }
            if (check(x[i] - l[j])) {
                one = x[i] + l[j];
                ok = 1;
                break;
            }
        }
        if (ok) break;
    }

    if (!ok) {
        cout << 0 << '\n';
        return;
    }
    test(check(0)); 
    cout << findr(one) << '\n';
    cout << findl(one);
}

signed main() {
	IO;	
	solve();	
}
