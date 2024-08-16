#include<iostream>
#include<queue>
#include<vector>

using namespace std;
signed main(){
    int n,m,k,ans=0;
    int t;

    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin>>n>>m>>k;

    vector<int> g[n];

    int in[n];
    for(int i=0;i<n;i++) in[i]=k;
    queue<int> q;
    cin>>t;
    for(int i=0;i<t;i++){
        int t;
        cin>>t;
        q.emplace(t);
    }

    int r[n][k],s[n][k];
    for(int i=0;i<n;i++){
        for(int j=0;j<k;j++){
            cin>>r[i][j];
            g[r[i][j]].push_back(i);
        }
    }

    for(int i=0;i<n;i++){
        for(int j=0;j<k;j++){
            cin>>s[i][j];
        }
    }

    vector<int> vis(n + 1, 0);
    while(!q.empty()) {
        int now=q.front();
        q.pop();
        if (vis[now]) continue;
        vis[now] = 1;

        for (int i : g[now]) {
            in[i]--;
            if(in[i]==0){
                for(int x=0;x<k;x++)q.push(s[i][x]);
                ans++;
            }
        }
    }
    cout<<ans;
}

