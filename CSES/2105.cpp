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
#define inf 1000000000
#define INF 1000000000000000000
#define mod 1000000007
#define MOD 998244353
#define get_bit(x, y) ((x>>y)&1)
#define mkp make_pair
#define IO ios_base::sync_with_stdio(0); cin.tie(0);
void abc() {cerr << endl;}
template <typename T, typename ...U> void abc(T a, U ...b) {
    cerr << a << ' ', abc(b...);
}
#ifdef debug
#define test(args...) abc("[" + string(#args) + "]", args)
#else
#define test(args...) void(0)
#endif

template<class T> bool ckmin(T& a, const T& b) { return b<a ? a=b, 1 : 0; }
template<class T> bool ckmax(T& a, const T& b) { return a<b ? a=b, 1 : 0; }


struct SAM {
  struct state {
    int len, link, cnt;
    map<char, int> next;
  };

  static const int MAXLEN = 200000; 
  state st[MAXLEN * 2];
  int sz, last;
  vector<vector<int>> tree;

  SAM() {
    st[0].len = 0; st[0].link = -1;
    sz = 1; last = 0;
  }

  void extend(char c) {
    int cur = sz++;
    st[cur].len = st[last].len + 1;
    st[cur].cnt = 1;
    int p = last;
    while (p != -1 && !st[p].next.count(c)) {
      st[p].next[c] = cur;
      p = st[p].link;
    }
    if (p == -1) {
      st[cur].link = 0;
    } else {
      int q = st[p].next[c];
      if (st[p].len + 1 == st[q].len) {
        st[cur].link = q;
      } else {
        int clone = sz++;
        st[clone].len = st[p].len + 1;
        st[clone].next = st[q].next;
        st[clone].link = st[q].link;
        while (p != -1 && st[p].next[c] == q) {
          st[p].next[c] = clone;
          p = st[p].link;
        }
        st[q].link = st[cur].link = clone;
      }
    }
    last = cur;
  }

  void build_tree() {
    tree.resize(sz);
    for (int i = 1; i < sz; i++) {
      tree[st[i].link].eb(i);
    }
  }

  void dfs(int u = 0) {
    for (int v : tree[u]) {
      dfs(v);
      st[u].cnt += st[v].cnt; 
    }
  }
} sam;

inline void solve() {
    string s;
    cin >> s;
    for (char c : s) {
        sam.extend(c);
    }
    int ans = 0;
    for (int i = 1; i < sam.sz; i++) {
        ans += sam.st[i].len - sam.st[sam.st[i].link].len;
    }
    cout << ans << '\n';
}

signed main() {
	IO;	
	solve();	
}
