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

string str;
string input;
int cur = 0;
int err = 0;
int E();

char getToken() {
  if (cur >= SZ(str)) return '\0';
  return str[cur];
}

void advance() {
  cur++;
}

int B(int num) {
  if (isdigit(getToken())) {
    int res = num * 2 + (getToken() - '0');
    advance();
    return B(res);
  }
  return num;
}

int N() {
  if (getToken() == '0') {
    advance();
    return 0;
  } else {
    advance();
    return B(1);
  }
  err = 1;
  return -1;
}

int F() {
  if (getToken() == '-') {
    advance();
    return -1 * F();
  } else if (getToken() == '(') {
    advance();
    int res = E();
    if (getToken() != ')') 
      return -1;
    advance();
    return res;
  } else if (isdigit(getToken())) {
    return N();
  }
  err = 1;
  return -1;
}


int T_() {
  if (getToken() == '*') {
    advance();
    return F() * T_();
  } else {
    return 1;
  }
}

int T() {
  return F() * T_();
}

int E_() {
  if (getToken() == '+') {
    advance();
    return T() + E_();
  } else if (getToken() == '-') {
    advance();
    return -T() + E_();
  } else {
    return 0;
  }
}

int E() {
  return T() + E_();
}

int Q() {
  err = 0; cur = 0;
  int a = E();
  if (getToken() == '=') {
    advance();
  } else {
    err = 1;
  }
  int b = E();
  if (getToken() != '\0') err = 1;
  if (err) return 0;
  
  if (a == b) {
    test(a, b);
    test(str);
  }

  return a == b;
}

map<char, char> mp;
vector<char> sybols = {'+', '-', '*', '(', ')', '0', '1', '='};
vector<char> alphaset;
int vis[10];
int ans = 0;

bool check() {
  int sum = 0;
  int cnt = 0;
  for (char c : str) {
    if (c == '(') sum++;
    if (c == ')') sum--;
    if (sum < 0) return 0;
    if (c == '=') cnt++;
  }
  
  for (int i = 0; i < SZ(str) - 1; i++) {
    if ((i == 0 || !isdigit(str[i-1])) && str[i] == '0' && isdigit(str[i+1])) 
      return 0;
  }

  return sum == 0 && cnt == 1;
}

void dfs(int u, int n) {
  if (u == n) {
    str.clear();
    for (char c : input) {
      if (isalpha(c)) str.push_back(mp[c]);
      else str.push_back(c);
    }
  
    if (!check()) return;

    ans += Q();
    return;
  }
  for (int i = 0; i < 8; i++) {
    if (vis[i]) continue;
    vis[i] = 1;
    mp[alphaset[u]] = sybols[i];
    dfs(u + 1, n);
    vis[i] = 0;
  }
}

inline void solve() {
  cin >> input;
  set<char> st;
  for (char c : input) {
    if (isalpha(c)) 
      st.insert(c);
  }
  for (char c : st) 
    alphaset.eb(c);
  assert(SZ(alphaset) <= 8);
  dfs(0, SZ(alphaset));
  cout << ans << '\n';
}

signed main() {
	IO;	
	solve();	
}
