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

ll x[100005], y[100005];
int n;

ll check(pll p){
    ll ans = 0;
    for(int i = 0; i < n; i++){
        ans += abs(x[i] - p.fi); 
        ans += abs(y[i] - p.se);
    }
    return ans;
}

int main(){
    io
    cin >> n;
    for(int i = 0; i < n; i++){
        cin >> x[i] >> y[i];
    }
    sort(x, x + n);
    sort(y, y + n);
    if(n % 2){
        cout << x[n / 2] << " " << y[n / 2] << "\n"; 
    } else {
        cout << x[n/2-1] << " " << y[n/2-1] << "\n";
    }
    // `else{
    // `    ll a = x[n / 2 - 1] + x[n / 2];
    // `    ll b = y[n / 2 - 1] + y[n / 2];
    // `    a /= 2;
    // `    b /= 2;
    // `    vector <pll> v;
    // `    for(int i = -1; i < 2; i++){
    // `        for(int j = -1; j < 2; j++){
    // `            v.eb(a + i, b + j);
    // `        }
    // `    }
    // `    pll ans = pll(0, INF);
    // `    for(int i = 0; i < SZ(v); i++){
    // `        ll a = check(v[i]);
    // `        if(a < ans.se){
    // `            ans = pll(i, a);
    // `        }
    // `    }
    // `    cout << v[ans.fi].fi << " " << v[ans.fi].se << "\n";
    // `}
    return 0;
}
