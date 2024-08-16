#include<bits/stdc++.h>
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

const int mxN = 2e6 + 5;

int n, l;

int get_max(vector<int> &nums) {
    int mx = nums[0];
    int maxpre = nums[0];
    int mn = nums[0];
    int minpre = nums[0];
    int sum = nums[0];
    for (int i = 1; i < SZ(nums); i++) {
        sum += nums[i];
        int maxTemp = nums[i] + max(maxpre, 0ll);
        maxpre = maxTemp;
        mx = max(mx, maxTemp);
        int minTemp = nums[i] + min(minpre, 0ll);
        minpre = minTemp;
        mn = min(mn, minTemp);
    }
    if (mx < 0) {
        return mx;
    }
    return abs(max(mx, sum - mn));
}

int matching(string a, string b) {
    int m, n, ans = 0;
	a = "#" + a;
	b = "#" + b;
	m = SZ(b);
	n = SZ(a);
    vector<int> nxt(m + 1);
	for(int i = 2, j = 0; i < m; i++) {
		while(j and b[j + 1] != b[i]) j = nxt[j];
		if(b[j + 1] == b[i]) j++;
		nxt[i] = j;
	}
	for(int i = 1, j = 0; i < n; i++) {
		while(j and b[j + 1] != a[i]) j = nxt[j];
		if(b[j + 1] == a[i]) j++;
		if(j == m - 1) ans++, j = nxt[j];
	}
    return ans > 0;
}

string decode(string a) {
    for (int i = 0; i < SZ(a); i++) {
        a[i] = (a[i] - '0') + 'A';
    }
    return a;
}

inline void solve() {
    cin >> n >> l;
    string tmp, goal, pat;
    for (int i = 0; i < n; i++) {
        vector<int> a(l);
        for (int &j : a) cin >> j;
        int t = get_max(a);
        if (t < 0) t = -t;
        tmp = to_string(t);
        for (char c : tmp) goal.pb(c);
    }
    cin >> pat;

    if (SZ(goal) <= SZ(pat) && matching(pat, decode(goal))) cout << goal << '\n';
    else cout << -1 << '\n';
}

signed main() {
	IO;	
	solve();	
}
