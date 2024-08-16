#include<bits/stdc++.h>
#pragma GCC optimize("Ofast,unroll-loops")
#pragma loop-opt(on)
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,avx,avx2,fma,tune=native")
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

// lazytag segment tree
int n;
struct SegmentTree {
  vector<int> mx, mn, mx_id, mn_id, tag;

  SegmentTree(int _n): mx(_n * 4, -INF), 
                      mn(_n * 4, INF), mx_id(_n * 4, 0), mn_id(_n * 4, 0), tag(_n * 4) {}

  #define ls (x<<1)
  #define rs (x<<1)|1
  #define mid ((l+r)>>1)

  inline void up(int x) {
    if (mx[ls] < mx[rs]) {
      mx[x] = mx[rs];
      mx_id[x] = mx_id[rs];
    } else {
      mx[x] = mx[ls];
      mx_id[x] = mx_id[ls];
    }
    if (mn[ls] > mn[rs]) {
      mn[x] = mn[rs];
      mn_id[x] = mn_id[rs];
    } else {
      mn[x] = mn[ls];
      mn_id[x] = mn_id[ls];
    }
  }

  inline void push_tag(int x) {
    tag[x] ^= 1;
    swap(mx[x], mn[x]);
    mx[x] = -mx[x];
    mx[x] %= mod;
    if (mx[x] < 0) mx[x] += mod;
    mn[x] = -mn[x];
    mn[x] %= mod;
    if (mn[x] < 0) mn[x] += mod;
    swap(mx_id[x], mn_id[x]);
  }

  inline void down(int x) {
    if(!tag[x]) return;
    push_tag(ls);
    push_tag(rs);
    tag[x] = 0;
  }

  void build(vector<int> &a, int l = 0, int r = n - 1, int x = 1) {
    if(l == r) {
      mn[x] = mx[x] = a[l];
      mn_id[x] = mx_id[x] = l;
      return; 
    }
    build(a, l, mid, ls);	build(a, mid+1, r, rs);
    up(x);
  } 

  void modify(int a, int b, int l = 0, int r = n - 1, int x = 1) {
    if(a <= l and r <= b) {
      push_tag(x);
      return;
    }
    if (l != r) down(x);
    if(a <= mid) modify(a, b, l, mid, ls);
    if(b > mid) modify(a, b, mid+1, r, rs);
    up(x);
  }
};

inline void solve(int cas) {
  cin >> n;
  vector<int> a(n);
  for (int &i : a) cin >> i;

  SegmentTree seg(n + 5);
  seg.build(a);

  int ans = 0;
  int q; cin >> q;
  while (q--) {
    int l, r; 
    cin >> l >> r;
    seg.modify(l - 1, r - 1);
    ans += (seg.mx_id[1] + 1);
    //test(seg.mx_id[1]);
  }

  cout << "Case #" << cas << ": " << ans << '\n';
}

signed main() {
	IO;	
  int T; cin >> T;
  for (int i = 1; i <= T; i++) solve(i);	
}
