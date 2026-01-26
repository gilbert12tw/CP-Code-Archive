#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
#define int ll
#define pii pair<int, int>
#define f first
#define s second
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
#define inf 2000000001
#define INF 1000000000000000000
#define mod 1000000007
#define MOD 998244353
#define get_bit(x, y) ((x>>y)&1)
#define mkp make_pair
#define IO ios_base::sync_with_stdio(0); cin.tie(0);
template <typename... T> void _print(T... args) {
    ((cerr << args << ' '), ...);
    cerr << '\n';
}
#ifdef debug
#define test(args...) _print("[" + string(#args) + "]:", args)
#else
#define test(args...) void(0)
#endif

template<class T> bool ckmin(T& a, const T& b) { return b<a ? a=b, 1 : 0; }
template<class T> bool ckmax(T& a, const T& b) { return a<b ? a=b, 1 : 0; }

using point = pair<int, int>;
#define x first
#define y second

mt19937 gen(921222);

inline int sq(const int &x) {
    return x * x;
}

int dis2(const point &a, const point &b) {
    return sq(a.x - b.x) + sq(a.y - b.y);
}

inline void solve() {
    int n; 
    cin >> n;
    vector<point> pt(n);
    for (int i = 0; i < n; i++) {
        cin >> pt[i].x >> pt[i].y;
        pt[i].x += 1000000000;
        pt[i].y += 1000000000;
    }
    shuffle(ALL(pt), gen);
    
    unordered_map<int, vector<point>> mp;
    auto encode = [](int x, int y) -> int {
        return x * inf + y;
    };

    auto add_pt = [&mp, &encode](int g, point p) -> int {
        int gx = p.x / g; 
        int gy = p.y / g;
        mp[encode(gx, gy)].eb(p);
        return SZ(mp[encode(gx, gy)]);
    };

    int mn_dis = dis2(pt[0], pt[1]);
    int grid_size = ceil(sqrt(mn_dis)), nw_gs = grid_size;
    add_pt(grid_size, pt[0]);
    add_pt(grid_size, pt[1]);
    bool rebuild = false;

    for (int i = 2; i < n; i++) {
        int gx = pt[i].x / grid_size;
        int gy = pt[i].y / grid_size;
        for (int dx = -1; dx <= 1; dx++) {
            for (int dy = -1; dy <= 1; dy++) {
                int nx = gx + dx;
                int ny = gy + dy;
                for (auto v : mp[encode(nx, ny)]) {
                    int d2 = dis2(v, pt[i]);
                    if (d2 < mn_dis) {
                        mn_dis = d2;
                        int gs = ceil(sqrt(mn_dis));
                        if (gs < nw_gs) {
                            nw_gs = gs;
                            rebuild = true;
                        }
                    }
                }
            }
        }

        int tmp = add_pt(grid_size, pt[i]);
        if (tmp > 10 && rebuild) {
            mp.clear();
            for (int j = 0; j <= i; j++) {
                add_pt(nw_gs, pt[j]);
            }
            rebuild = false;
            grid_size = nw_gs;
        }
    }
    cout << mn_dis << '\n';
}

signed main() {
	IO;	
	solve();	
}
