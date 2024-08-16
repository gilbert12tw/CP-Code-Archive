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
#define vi vector<int>
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
#define MOD 998244353
#define get_bit(x, y) ((x>>y)&1)
#define mkp make_pair
#define IO ios_base::sync_with_stdio(0); cin.tie(0);
void abc() {cout << endl;}
template <typename T, typename ...U> void abc(T a, U ...b) {
    cout << a << ' ', abc(b...);
}
#ifdef loli
#define test(args...) abc("[" + string(#args) + "]", args)
#else
#define test(args...) void(0)
#endif

template<class T> bool ckmin(T& a, const T& b) { return b<a ? a=b, 1 : 0; }
template<class T> bool ckmax(T& a, const T& b) { return a<b ? a=b, 1 : 0; }

const int offset = 30000;
bitset<60005> m1, m3, rm3;

inline int rev(int x) {
    return 60000 - x;
}

inline void solve() {
    int n1, n2, n3;
    cin >> n1;
    for (int i = 0; i < n1; i++) {
        int x; cin >> x;
        m1.set(x + offset);
        test(x + offset);
    }
    cin >> n2;
    vector<int> v(n2);
    for (int &i : v) { 
        cin >> i;
        i += offset;
        test(i);
    }
    
    cin >> n3;
    for (int i = 0; i < n3; i++) {
        int x; cin >> x;
        rm3.set(rev(x + offset));
    }

    int ans = 0;
    for (int i : v) {
        int ri = rev(i);
        bitset<60005> tmp;
        test(i, ri);
        if (i < ri) {
            tmp = (rm3 >> (ri - i));
        } else {
            tmp = (rm3 << (i - ri));
        }
        ans += (tmp & m1).count();
    }
    cout << ans << '\n';
}

signed main() {
	IO;	
	solve();	
}
