#include <bits/stdc++.h>
#define rep(i,j,k) for (int i=j; i<=k; i++)
#define ff first
#define ss second
#define pb push_back
#define mp make_pair
#define de(x) cout << #x << '=' << x << ", "
#define dd cout << endl;
#define roadroller ios::sync_with_stdio(0), cin.tie(0);
using namespace std;
typedef pair<int,int> pii;

const int N = 410;

int n, l;
vector<int> a[N];
string pat;

int solve(vector<int> b){
    vector<int> dp(n);
    int tot = 0, ovo = 0;
    for (int i=0; i<n; i++){
        if (i == 0){
            dp[i] = b[i];
        }
        else{
            dp[i] = min(b[i], dp[i-1] + b[i]);
        }
        ovo = min(ovo, dp[i]);
        tot += b[i];
    }

    vector<int> dp2(n);
    int tot2 = -1e9;
    for (int i = 0; i < n; i++) {
        if (i) dp2[i] = max(b[i], dp2[i-1] + b[i]);
        else dp2[i] = b[i];
        tot2 = max(tot2, dp2[i]); 
    }

    return abs(max(tot - ovo, tot2));
}

string toa(int n){
    return to_string(n);
}

string decode(string s){
    for (int i=0; i < s.size(); i++){
        s[i] = 'A' + (s[i] - '0');
    }
    return s;
}

vector<int> prefix_function(string s) {
  int n = (int)s.length();
  vector<int> pi(n);
  for (int i = 1; i < n; i++) {
    int j = pi[i - 1];
    while (j > 0 && s[i] != s[j]) j = pi[j - 1];
    if (s[i] == s[j]) j++;
    pi[i] = j;
  }
  return pi;
}

int find_occurrences(string text, string pattern) {
  string cur = pattern + '#' + text;
  int sz1 = text.size(), sz2 = pattern.size();
  vector<int> v;
  vector<int> lps = prefix_function(cur);
  for (int i = sz2 + 1; i <= sz1 + sz2; i++) {
    if (lps[i] == sz2)
      v.push_back(i - 2 * sz2);
  }
  return v.size();
}

signed main(){
    cin >> n >> l;
    rep(i,1,n){
        a[i].resize(l);
        for (int j=0; j<l; j++){
            cin >> a[i][j]; 
        }
    }  
    cin >> pat;

    string s = "";
    rep(i,1,n){
        int sum = solve(a[i]);
        s += toa(sum);
    }
    
    if (find_occurrences(pat, decode(s))){
        cout << s << '\n';
    }
    else{
        cout << -1 << '\n';
    }
}
