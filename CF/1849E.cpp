#include<bits/stdc++.h>
//#define loli
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

const int mxN = 1e6 + 5;
int n;
int a[mxN];
int ans = 0;
int rmx[mxN], rmn[mxN], lmx[mxN], lmn[mxN];

void dq(int l, int r) {
    if (l == r) return;
    int mid = (l + r) >> 1;
    for (int i = mid; i >= l; i--) {
        if (i == mid) lmn[i] = lmx[i] = i;
        else {
            lmn[i] = (a[i] < a[lmn[i+1]] ? i : lmn[i+1]);
            lmx[i] = (a[i] > a[lmx[i+1]] ? i : lmx[i+1]);
        }
    }
    for (int i = mid+1; i <= r; i++) {
        if (i == mid+1) rmn[i] = rmx[i] = i;
        else {
            rmn[i] = (a[i] < a[rmn[i-1]] ? i : rmn[i-1]);
            rmx[i] = (a[i] > a[rmx[i-1]] ? i : rmx[i-1]);
        }
    }

    // 3 cases
    int j;
    // rmn, rmx
    for (int i = mid+1, j = mid+1; i <= r; i++) {
        if (rmx[i] <= rmn[i]) continue;
        while (j - 1 >= l && a[lmn[j-1]] > a[rmn[i]] && a[lmx[j-1]] < a[rmx[i]]) j--;
        ans += (mid + 1 - j);
    }

    // lmn, lmx
    for (int i = mid, j = mid; i >= l; i--) {
        if (lmx[i] <= lmn[i]) continue;
        while (j + 1 <= r && a[rmn[j+1]] > a[lmn[i]] && a[rmx[j+1]] < a[lmx[i]]) j++;
        ans += (j - mid);
    }

    // lmn, rmx;
    int jl, jr;
    for (int i = mid+1, jl = mid+1, jr = mid+1; i <= r; i++) {
        while (jr - 1 >= l && a[lmx[jr-1]] < a[rmx[i]]) jr--;
        while (jl - 1 >= l && a[lmn[jl-1]] > a[rmn[i]]) jl--;
        test(jr, jl, l, r);
        ans += max(0ll, jl - jr);
    }

    dq(l, mid); dq(mid+1, r);
}

inline void solve() {
    cin >> n;
    for (int i = 1; i <= n; i++) cin >> a[i];

    dq(1, n);
    
    cout << ans;
}

signed main() {
	IO;	
	solve();	
}
