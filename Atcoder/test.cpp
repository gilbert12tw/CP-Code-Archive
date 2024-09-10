#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define int long long

map<pair<int, int>, int> mp;

int calc(int x, int y, int n) {
  if (x == 0 || y == 0)
    return 0;
  if (n == 0)
    return 1;
  if (mp[make_pair(x, y)])
    return mp[make_pair(x, y)];
  int mid = (1LL) << (n - 1);
  int ans = calc(min(mid, x), min(mid, y), n - 1);
  if (x > mid)
    ans += calc(x - mid, min(mid, y), n - 1);
  if (y > mid)
    ans += calc(min(mid, x), y - mid, n - 1);
  mp[make_pair(x, y)] = ans;
  return ans;
}

int X1, Y1, X2, Y2;

void solve() {
  cin >> X1 >> Y1 >> X2 >> Y2;
  cout << calc(X2, Y2, 39) - calc(X1 - 1, Y2, 39) - calc(X2, Y1 - 1, 39) +
              calc(X1 - 1, Y1 - 1, 39)
       << '\n';
}

signed main() {
  ios::sync_with_stdio(0);
  cin.tie(0);
  solve();
}
