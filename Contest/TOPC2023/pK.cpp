#include <bits/stdc++.h>
#pragma GCC optimize("O2")
using namespace std;

typedef pair<int, int> pii;
typedef long long ll;
typedef pair<ll, ll> pll;
#define fi first
#define se second
#define io ios_base::sync_with_stdio(0); cin.tie(0);
#define setpr setprecision
#define ef emplace_front
#define eb emplace_back
#define pb push_back
#define em emplace
#define ppb pop_back
#define pf pop_front
#define lowb lower_bound
#define uppb upper_bound
#define lowbit(x) ((x) & -(x))
const ll M = 1e9 + 7;
const ll INF = 1e14;

#define N 5000050 // |s| + |t|
int z[N];

int solve(string s, int len){
    int ans = 0; z[0] = 0;
    for(int i = 1, j = 0; i < s.length(); i++){
        int i2 = i - j;
        if(j + z[j] <= i || j + z[j] == i + z[i2]){
            z[i] = j + z[j] <= i ? 0 : z[i2]; j = i;
            while(s[z[i]] == s[i + z[i]]) z[i]++;
        }
        else if(j + z[j] > i + z[i2]) z[i] = z[i2];
        else z[i] = z[j] - i2;
        if(z[i] == len) ans++;
    }
    return ans;
}

int main(){
    io
    string s;
    cin >> s;
    int len = s.length();
    s = "kick_" + s;
    int ans = solve(s, 4);
    cout << ans << "\n";
    return 0;
}
