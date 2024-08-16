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

struct Stack {
  int tp = 0;
  int stk[1000001];
  void push(int x) { stk[tp++] = x; }
  bool empty() { return tp == 0; }
  void clear() { tp = 0; }
  int pop() { 
    assert(!empty());
    return stk[tp--]; 
  }
  int top() { 
    assert(!empty());
    return stk[tp-1]; 
  }
};

inline void solve() {
  string s; cin >> s;
  int n = SZ(s);
  Stack stk;
  
  int start = -1, ans = 0;
  for (int i = 0; i < n; i++) {
    if (s[i] == '(') stk.push(i);
    else {
      if (stk.empty()) {
        start = i;
      } else {
        stk.pop();
        if (stk.empty()) 
          ans = max(ans, i - start);
        else 
          ans = max(ans, i - stk.top());
      }
    }
  }
  char out = 'a' + ((ans / 2) % 26);
  cout << out;
}

signed main() {
	IO;	
  int T; cin >> T;
	while (T--) solve();	
  cout << '\n';
}
