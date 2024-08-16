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

string s;
int id = 0;
int cal();

// id
// 2+3*1+2+1
//   i 
int getnum() {
    int res = 0;
    while (isdigit(s[id])) 
        res = res * 10 + (s[id++] - '0');
    return res;
}

//f(1+2,3*10,105)
//  i

int fcal() {
    id += 2; // f(
    int mn = INF, mx = -INF;
    while (s[id] != ')') {
        int tmp = cal();
        mn = min(mn, tmp);
        mx = max(mx, tmp);
        if (s[id] == ',') id++;
    }
    id++; // )
    return mx - mn;
}


int cal() {
    vector<int> num, opt;
    while (id < SZ(s) && s[id] != ',' && s[id] != ')') {
        if (isdigit(s[id]) || s[id] == 'f') {

            if (s[id] != 'f') num.eb(getnum());
            else num.eb(fcal());

            // 1+2
            // num : 1 2
            // opt : 0
            if (!opt.empty() && opt.back() == 0) {
                int u = num.back(); num.pop_back();
                int v = num.back(); num.pop_back();
                num.eb(u + v);
                opt.pop_back();
            }
        } else if (s[id] == '*'){
            opt.emplace_back(1); 
            id++;
        } else if (s[id] == '+'){
            opt.emplace_back(0);
            id++;
        }
    }
    int res = 1;
    for (int i : num) res *= i;
    return res;
}

inline void solve() {
    cin >> s;
    cout << cal() << endl;
}

signed main() {
	IO;	
	solve();	
}
