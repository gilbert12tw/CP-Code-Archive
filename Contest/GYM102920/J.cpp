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

bitset<501> b[501];
bitset<501> bid[501];

int n;
void insert(bitset<501> &x, int id) {
    bitset<501> tmpid;
    tmpid.set(id);
    for (int i = 0; i < n; i++) {
        if (x[i] == 1) {
            if (b[i][i] == 0) {
                bid[i] = tmpid;
                b[i] = x;
                break;
            } else {
                x ^= b[i];
                tmpid ^= bid[i];
            }
        }
    }
}

vector<int> eli(bitset<501> &x) {
    bitset<501> tmpid;
    for (int i = 0; i < n; i++) {
        if (x[i] == 1 && b[i][i]) {
            x ^= b[i];
            tmpid ^= bid[i];
        }
    }
    if (x.any()) 
        return {-1};

    vector<int> res;
    for (int i = 0; i < n; i++) {
        if (tmpid[i]) res.eb(i + 1);
    }
    return res;
}

inline void solve() {
    cin >> n;
    for (int i = 0; i < n; i++) {
        bitset<501> tmp;
        for (int j = 0; j < n; j++) {
            int x; cin >> x;
            if (x) tmp.set(j);
        }
        insert(tmp, i);
    }
    
    vector<vector<int>> ans;
    for (int i = 0; i < n; i++) {
        bitset<501> tmp;
        tmp.set(i);
        vector<int> res;
        res = eli(tmp);
        if (!res.empty() && res[0] == -1) {
            cout << -1 << '\n';
            return;
        } else {
            ans.eb(res);
        }
    }
    for (auto res : ans) {
        for (int i = 0; i < SZ(res); i++)
            cout << res[i] << " \n"[i == SZ(res) - 1];
    }
}

signed main() {
	IO;	
	solve();	
}
