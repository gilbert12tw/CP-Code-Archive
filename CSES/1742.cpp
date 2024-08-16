#include<bits/stdc++.h>
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

const int mxN = 2e5 + 5;

int n;

#define ls (id<<1)
#define rs (ls|1)

struct segment_tree {
    set<int> seg[mxN * 4];

    void modify(int ql, int qr, int v, int l = 0, int r = mxN, int id = 1) {
        if (ql <= l && r <= qr) {
            if (v == 2) test(l, r);
            seg[id].insert(v);
            return;
        }
        int mid = (l+r) >> 1;
        if (ql <= mid) modify(ql, qr, v, l, mid, ls);
        if (qr > mid) modify(ql, qr, v, mid+1, r, rs);
    }

    pii query(int ql, int qr, int pos, int l = 0, int r = mxN, int id = 1) {
        auto itl = seg[id].lower_bound(ql);
        auto itr = seg[id].upper_bound(qr);
        int ansl = INF, ansr = -INF;
        if (itl != seg[id].end() && *itl <= qr) ansl = *itl;
        if (itr != seg[id].begin() && *prev(itr) >= ql) ansr = *prev(itr);

        if (l == r) 
            return mkp(ansl, ansr);
        
        int mid = (l+r) >> 1;
        pii tmp;

        if (pos <= mid) tmp = query(ql, qr, pos, l, mid, ls);
        else tmp = query(ql, qr, pos, mid+1, r, rs);

        if (tmp.F != INF) ansl = min(ansl, tmp.F); 
        if (tmp.S != INF) ansr = max(ansr, tmp.S); 
        return mkp(ansl, ansr);
    }

} segX, segY;

inline void solve() {
    cin >> n;
    vector<pii> path;
    vector<int> tmpx, tmpy;
    path.eb(0, 0);
    tmpx.eb(0);
    tmpy.eb(0);

    char pc = '0';
    int tmp = 0, mn = -1;
    for (int i = 0; i < n; i++) {
        char c; int x;
        cin >> c >> x;     
        if ((c == 'U' && pc == 'D') || (c == 'D' && pc == 'U') || 
            (c == 'L' && pc == 'R') || (c == 'R' && pc == 'L')) {
            if (mn == -1) mn = tmp;
        }
            
        tmp += x;
        pii pt = path.back();
        if (c == 'U') {
            pt.Y -= x;
            tmpy.eb(pt.Y);
        } else if (c == 'D') {
            pt.Y += x;
            tmpy.eb(pt.Y);
        } else if (c == 'R') {
            pt.X += x;
            tmpx.eb(pt.X);
        } else {
            pt.X -= x;
            tmpx.eb(pt.X);
        }
        path.eb(pt);
        pc = c;
    }

    sort(ALL(tmpx));
    sort(ALL(tmpy));
    uni(tmpx);
    uni(tmpy);

    map<int, set<int>> mpx, mpy;
    mpx[0].insert(0);
    mpy[0].insert(0);

    int ans = 0;
    for (int i = 1; i <= n; i++) {
        // move UD
        if (path[i].X == path[i-1].X) {
            int pl = min(path[i].Y, path[i-1].Y), pr = max(path[i].Y, path[i-1].Y);
            int l = lb(tmpy, pl) - tmpy.begin();
            int r = lb(tmpy, pr) - tmpy.begin();

            if (path[i].Y > path[i-1].Y) pl++;
            else pr--;

            pii meet = segX.query(pl, pr, lb(tmpx, path[i].X) - tmpx.begin());

            int len = INF;
            auto itl = mpy[path[i].X].lower_bound(pl);
            auto itr = mpy[path[i].X].upper_bound(pr);

            // cursh
            if (itl != mpy[path[i].X].end() && *itl <= pr) 
                len = min(len, abs(path[i-1].Y - *itl));
            if (itr != mpy[path[i].X].begin() && *prev(itr) >= pl) 
                len = min(len, abs(path[i-1].Y - *prev(itr)));
            if (meet.F != INF) 
                len = min({len, abs(path[i-1].Y - meet.F), abs(path[i-1].Y - meet.S)});

            if (len != INF) {
                test(meet.F, meet.S);
                ans += len;
                break;
            }

            segY.modify(l, r, path[i].X);
            ans += abs(path[i].Y - path[i-1].Y);
            mpy[path[i].X].insert(path[i].Y);
        } else { // move LR
            int pl = min(path[i].X, path[i-1].X), pr = max(path[i].X, path[i-1].X);
            int l = lb(tmpx, pl) - tmpx.begin();
            int r = lb(tmpx, pr) - tmpx.begin();

            if (path[i].X > path[i-1].X) pl++;
            else pr--;

            pii meet = segY.query(pl, pr, lb(tmpy, path[i].Y) - tmpy.begin());

            int len = INF;
            auto itl = mpx[path[i].Y].lower_bound(pl);
            auto itr = mpx[path[i].Y].upper_bound(pr);

            // cursh
            if (itl != mpx[path[i].Y].end() && *itl <= pr) 
                len = min(len, abs(path[i-1].X - *itl));
            if (itr != mpx[path[i].Y].begin() && *prev(itr) >= pl) 
                len = min(len, abs(path[i-1].X - *prev(itr)));
            if (meet.F != INF) 
                len = min({len, abs(path[i-1].X - meet.F), abs(path[i-1].X - meet.S)});

            if (len != INF) {
                test(meet.F, meet.S);
                ans += len;
                break;
            }
             
            segX.modify(l, r, path[i].Y);
            ans += abs(path[i].X - path[i-1].X);
            mpx[path[i].Y].insert(path[i].X);
        }

    }
    if (mn != -1) ans = min(ans, mn);
    cout << ans << '\n';
}

signed main() {
	IO;	
	solve();	
}
