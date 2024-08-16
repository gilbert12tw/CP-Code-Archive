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

#define vv vector<vector<int>>

vv rotate(const vv &mat, int x, int y) {
    int h = mat.size();
    int w = mat[0].size();
    vv res = mat;
    for (int i = 1; i <= h - 1; i++) {
        for (int j = 1; j <= w - 1; j++) {
            res[h - i + x - 1][w - j + y - 1] = mat[i + x - 1][j + y - 1];
        }
    }
    return res;
}

map<vv, int> bfs(vv st) {
    int h = st.size();
    int w = st[0].size();
    queue<vv> q; 
    map<vv, int> dis;
    q.push(st);
    dis[st] = 0;
    while (!q.empty()) {
        auto mat = q.front(); q.pop();
        int d = dis[mat];
        test(d);
        if (d >= 10) continue;

        for (int i = 0; i < 2; i++) {
            for (int j = 0; j < 2; j++) {
                vv tmp = rotate(mat, i, j);
                if (dis.find(tmp) == dis.end()) {
                    dis[tmp] = d + 1;
                    q.push(tmp);
                }
            }
        }
    }
    return dis;
}

void printm(vv mat) {
    cout << '\n';
    for (int i = 0; i < mat.size(); i++) {
        for (int j = 0; j < mat[0].size(); j++) {
            cout << mat[i][j] << ' ';
        }
        cout << '\n';
    }
}

inline void solve() {
    int n, m;
    cin >> n >> m;
    vv mat(n, vector<int>(m));
    vv ori = mat;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> mat[i][j];
            ori[i][j] = i * m + j + 1;
        }
    }
    
    auto mp1 = bfs(mat);
    auto mp2 = bfs(ori);

    int ans = -1;
    for (auto [mt, dis] : mp1) {
        if (mp2.find(mt) != mp2.end()) {
            int d = dis + mp2[mt];
            if (ans == -1 || d < ans) {
                ans = d;
            }
        }
    }
    cout << ans << '\n';
}

signed main() {
	IO;	
	solve();	
}
