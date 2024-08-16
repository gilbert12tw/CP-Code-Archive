#include<bits/stdc++.h>
#define loli
using namespace std;
typedef long long ll;
#define int ll
#define pii pair<int, int>
#define x first
#define y second
#define X first
#define Y second
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

int n, t;
struct Segment {
    pii st, ed;
    Segment (pii _s, pii _e) : st(_s), ed(_e) {}
    int len() {
        return ed.x - st.x + ed.y - st.y;
    }
    bool operator ^ (Segment &b) {
        if (st.x == ed.x && b.st.y == b.ed.y) {
            if (b.st.x <= st.x && st.x <= b.ed.x &&
                st.y <= b.st.y && b.st.y <= ed.y)
                return 1;
            return 0;
        } else if (st.y == ed.y && b.st.x == b.ed.x) {
            if (st.x <= b.st.x && b.st.x <= ed.x &&
                b.st.y <= st.y && st.y <= b.ed.y)
                return 1;
            return 0;
        }
        return 0;
    }
};

pii inter_pt(Segment &a, Segment &b) {
    if (a.st.x == a.ed.x && b.st.y == b.ed.y) {
        return mkp(a.st.x, b.st.y);
    } 
    return mkp(b.st.x, a.st.y);
}

vector<Segment> seg;
int mat[501][501];
pii inter[501][501];
bitset<501> vis;

int cir = 0;
void dfs(int u) {
    vis[u] = 1;
    cir += seg[u].len();
    for (int i = 0; i < n; i++) {
        if (!vis[i] && mat[u][i]) 
            dfs(i);
    }
}

inline void solve() {
    cin >> n >> t;
    pii begin(-1, -1);
    for (int i = 0; i < n; i++) {
        pii st, ed;
        cin >> st >> ed;
        if (begin == mkp(-1ll, -1ll)) 
            begin = st;
        if (st.x == ed.x && st.y > ed.y) swap(st, ed);
        if (st.y == ed.y && st.x > ed.x) swap(st, ed);
        seg.eb(Segment(st, ed));
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i == j) continue;
            if (seg[i] ^ seg[j]) {
                mat[i][j] = 1;
                inter[i][j] = inter_pt(seg[i], seg[j]);
            }
        }
    }
    dfs(0);
    
    int cur_direction = 0;
    if (seg[0].st.x == seg[0].ed.x) {
        if (begin == seg[0].st) 
            cur_direction = 0;
        else 
            cur_direction = 2;
    } else {
        if (begin == seg[0].st) 
            cur_direction = 1;
        else 
            cur_direction = 3;
    }
}

signed main() {
	IO;	
	solve();	
}
