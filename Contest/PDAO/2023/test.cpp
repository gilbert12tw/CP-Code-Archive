#include <bits/stdc++.h>
using namespace std;
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    int n,t,ans=0;
    cin>>n>>t;
    int a[n+1];
    for(int i=1;i<=n;i++){
        cin>>a[i];
        a[i]+=a[i-1];
    }
    int pt1=1,pt2=0;
    while(pt2 < n){
        if(pt2 < n && a[pt2+1]-a[pt1-1]<=t){
            pt2++;
        }
        else pt1++;
        if(pt2-pt1 > ans) ans = pt2 - pt1 + 1;
    }
    cout<<ans;
}
