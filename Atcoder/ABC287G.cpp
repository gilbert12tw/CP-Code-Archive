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

int n, total_cards;
int tsz;
vector<pii> card;
vector<pii> qry;
vector<int> tmp;

class Segment {
public:
    int score, cnt;
    Segment() {
        score = 0;
        cnt = 0;
    }
};
Segment seg[mxN * 4];

#define mid ((l+r)>>1)
#define ls (id<<1)
#define rs ((id<<1)|1)

void modify(int pos, int val, int id = 1, int l = 0, int r = tsz) {
    if (l == r) {
        seg[id].cnt += val;
        seg[id].score = tmp[l] * seg[id].cnt;
        return;
    }
    if (pos <= mid) modify(pos, val, ls, l, mid);
    else modify(pos, val, rs, mid+1, r);

    seg[id].cnt = seg[ls].cnt + seg[rs].cnt;
    seg[id].score = seg[ls].score + seg[rs].score;
}

int findk(int goal, int id = 1, int l = 0, int r = tsz) {
    if (l == r) return goal * tmp[l];
    if (goal >= seg[rs].cnt) return seg[rs].score + findk(goal - seg[rs].cnt, ls, l, mid);
    else return findk(goal, rs, mid+1, r);
}

inline void solve() {
    cin >> n;
    for (int i = 0; i < n; i++) {
        int a, b; cin >> a >> b;
        tmp.eb(a);
        card.eb(a, b);
        total_cards += b;
    }
    
    int q; cin >> q;
    while (q--) {
        int o, x, y; cin >> o;
        if (o == 1) {
            cin >> x >> y;
            qry.eb(x, y);
            tmp.eb(y);
        } 
        else if (o == 2) {
            cin >> x >> y;
            qry.eb(-x, y);
        }
        else {
            cin >> x;
            qry.eb(0, x);
        }
    }
    
    sort(ALL(tmp));
    uni(tmp);
    tsz = SZ(tmp);
    for (int i = 0; i < n; i++) {
        card[i].F = lb(tmp, card[i].F) - tmp.begin();
        modify(card[i].F, card[i].S);
    }

    for (auto [x, y] : qry) {
        if (x == 0) {
            if (total_cards < y) cout << -1 << '\n';
            else cout << findk(y) << '\n';
        }
        else if (x > 0) { // change score
            x--;
            modify(card[x].F, -card[x].S);
            card[x].F = lb(tmp, y) - tmp.begin();
            modify(card[x].F, card[x].S);
        }
        else { // change cnt
            x = -x; x--;
            total_cards += (y - card[x].S);
            modify(card[x].F, y - card[x].S);
            card[x].S = y;
        }
    }
}

signed main() {
	IO;	
	solve();	
}
