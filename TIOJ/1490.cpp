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
#define wopen(x) freopen((x),"w",stdout)
#define ropen(x) freopen((x),"r",stdin)
using namespace std;

int n, sum, mx, m[10005];
signed main(){
    ios_base::sync_with_stdio(0);cin.tie(0);
    while(cin>>n && n){
        sum = mx = 0;
        for(int i = 0; i < n; i++) cin>>m[i], sum += m[i];
        sort(m, m+n, greater<int>());
        if(sum&1 || m[0] > n - 1){
            cout<<"no\n";
            continue;
        }
        bool ok = 1;
        for(int i = 0; i < n && ok; i++){
            int j = i+1, cnt = 0;
            while(cnt < m[i] && j < n){
                if(m[j]){
                    m[j]--;
                    cnt++;
                }
                j++;
            }
            m[i] -= cnt;
            sort(m+i+1, m+n, greater<int>());
        }
        for(int i = 0; i < n; i++)
            if(m[i]) ok = 0;
        cout << (ok ? "yes\n" : "no\n");
    }
}

