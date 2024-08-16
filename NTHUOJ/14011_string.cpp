#include<bits/stdc++.h>
#pragma GCC optimize("Ofast,unroll-loops")
#pragma loop-opt(on)
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,avx,avx2,fma,tune=native")
using namespace std;
#define IO ios_base::sync_with_stdio(0); cin.tie(0);
#define pb push_back

string lft, rgt;

inline void solve() {
  string opr;
  while (cin >> opr) {
    string input; int n;
    if (opr[0] == 'T') {
      cin >> input;
      for (char c : input) lft.pb(c);
    } else if (opr[0] == 'M'){
      cin >> n;
      if (n > 0) {
        while (!rgt.empty() && n > 0) {
          n--;
          lft.pb(rgt.back());
          rgt.pop_back();
        }
      } else if (n < 0) {
        n = -n;
        while (!lft.empty() && n > 0) {
          n--;
          rgt.pb(lft.back());
          lft.pop_back();
        }
      }
    } else if (opr[0] == 'B') {
      if (!lft.empty()) lft.pop_back();
    } else if (opr[0] == 'P') {
      cout << lft;
      for (int i = rgt.size() - 1; i >= 0; i--)
        cout << rgt[i];
      cout << '\n';
    }
  }
}

signed main() {
	IO;	
	solve();	
}
