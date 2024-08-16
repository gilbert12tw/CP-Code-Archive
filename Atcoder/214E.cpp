#include<bits/stdc++.h>
using namespace std;
#define int long long
#define pb push_back
#define f first
#define s second
#define pii pair<int,int>
const int N=2e5+5;
int n;
pii b[N];
signed main(){
    ios::sync_with_stdio(0);cin.tie(0);
    int t;
    cin>>t;
    while(t--){
        cin>>n;
        for(int i=0;i<n;i++) cin>>b[i].f>>b[i].s;
        sort(b,b+n, [](int x, int y) {
            if (b[x].s == b[y].s) return 
        });
        map<int,bool> m;
        m[-1]=1;
        bool ans=1;
        for(int i=0;i<n;i++){
            auto it=--m.upper_bound(b[i].s);
            if(it->f==b[i].s){ans=0;break;}
            else{
                int k=it->f;
                if( k < b[i].f ) m[b[i].f]=1;
                else m[k+1]=1;
            }
        }//for(auto e:m) cout<<(e.f)<<" ";cout<<"\n";
        if(ans) cout<<"Yes\n";
        else cout<<"No\n";
    }
}
