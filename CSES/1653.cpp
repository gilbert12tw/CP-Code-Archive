#include<bits/stdc++.h>
#define x first
#define y second
#define all(x) (x).begin(),(x).end()
#define sz(x) (int)(x).size()
#define mem(x,val) memset(x,val,sizeof x)
#define pii pair<int,int>
#define pb emplace_back
#define ar array
#define int long long
#define FOR(i, a, b) for(int i = a; i < b; i++)
#define F0R(i, n) FOR(i, 0, n)
#define FOR1(i, n) FOR(i, 1, n+1)
#define wopen(x) freopen((x),"w",stdout)
#define ropen(x) freopen((x),"r",stdin)
using namespace std;
const int dx[] = {1, 0, -1, 0}, dy[] = {0, 1, 0, -1};
 
int n, x, w[25];
pii dp[(1<<20)+1];
 
pii best(pii a, pii b){
    return min(a, b);
}
 
signed main(void){
    ios_base::sync_with_stdio(0); cin.tie(0);
    cin >> n >> x;
    for(int i = 0; i < n; i++) cin >> w[i];
    for(int i = 1; i < (1<<n); i++) dp[i] = {n + 1, x + 1};
    dp[0] = {0, 0};
    for(int i = 1; i < (1<<n); i++){
        for(int j = 0; j < n; j++){
            if((i>>j)&1){
                if(dp[i^(1<<j)].y + w[j] <= x) dp[i] = best(dp[i], {dp[i^(1<<j)].x, dp[i^(1<<j)].y + w[j]});
                else dp[i] = best(dp[i], {dp[i^(1<<j)].x + 1, w[j]});
            }
        }
    }
    cout << dp[(1<<n)-1].x + 1 << '\n';
}
