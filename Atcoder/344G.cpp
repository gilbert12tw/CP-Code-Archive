#include<bits/stdc++.h>
#define loli
using namespace std;
typedef long long ll;
#define int ll
#define pii pair<int, int>
#define x first
#define y second
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

#define ppi pair<pii, int>

long long g;
long long md = ((1ll<<31)-1);
long long gen() {
  g = (48271 * g) % md;
  return g;
}

int cross(pii a, pii b) {
    int res = a.x * b.y - a.y * b.x;
    if (res > 0) return 1;
    if (res == 0) return 0;
    return -1;
}

pii sub(pii a, pii b) {
    return mkp(a.x - b.x, a.y - b.y);
}

inline void solve() {

    int n; cin >> n;
    vector<pii> pt(n);
    for (pii &i : pt) cin >> i.x >> i.y;

    priority_queue<ppi, vector<ppi>, decltype(
        [](ppi a, ppi b) {
            int c = cross(a.x, b.x);
            if (c == 0) return a.y < b.y;
            return c > 0;
        }
    )> pq;

    sort(ALL(pt));
    for (int i = 1; i < n; i++) {
        pq.push(mkp(sub(pt[i], pt[i-1]), i));
    }

    int q, ra, rb;
    cin >> q >> g >> ra >> rb;
    vector<pii> ask;
    test(q);
    for(long long i = 0;i < q; i++) {
        long long g1 = gen();
        long long g2 = gen();
        long long g3 = gen();
        long long a = -ra + (g1 % ((ra<<1) + 1));
        long long b = -rb + ((g2 * md + g3) % ((rb<<1) | 1));
        test(a, b);
        ask.eb(a, b);
    }
    
    sort(ALL(ask));

    int res = 0;
    for (int i = 0; i < q; i++) {
        int a = ask[i].x;
        int b = ask[i].y;

        while (!pq.empty()) {
            if (cross(mkp(1, a), pq.top().x) < 0) break;

            auto [ln, id] = pq.top(); pq.pop();
            if (ln != sub(pt[id], pt[id-1])) 
                continue;

            swap(pt[id], pt[id-1]);

            //if (id - 1 > 0 && pt[id-2].x > pt[id-1].x) {
            if (id - 1 > 0) {
                pq.push(sub(pt[id-1], pt[id-2]), id-1);
            }
            //if (id + 1 < n && pt[id].x > pt[id+1].x) {
            if (id + 1 < n) {
                pq.push(sub(pt[id+1], pt[id]), id);
            }
        }

        // binary search

        if (a * pt[0].x + b > pt[0].y) {
            continue;
        }

        int l = 0, r = n - 1;
        while (l < r) {
            int mid = (l + r + 1) >> 1;
            if (a * pt[mid].x + b <= pt[mid].y) l = mid;
            else r = mid - 1;
        }
        test(l+1);
        res += (n - l + 1);
    }
    cout << res << '\n';
}

signed main() {
	IO;	
	solve();	
}
