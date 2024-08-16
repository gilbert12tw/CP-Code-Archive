#include<bits/stdc++.h>
#define fi first
#define se second
#define pb emplace_back
#define all(n) (n).begin(),(n).end()
#define ll long long
#define pii pair<int,int>
#define mem(a,val) memset(a,val,sizeof(a))
#define speed ios_base::sync_with_stdio(0);cin.tie(0);
 
using namespace std;
 
const int dx[8] = {2,2,-2,-2,1,1,-1,-1}, dy[8] = {1,-1,1,-1,2,-2,2,-2};
int x,y,t[10][10],ans[10][10];
 
bool check(int x,int y){
    return x>0&&x<9&&y>0&&y<9&&t[x][y] == 0;
}

int cnt(int x,int y){
    int res = 0;
    for(int i = 0; i < 8; i++){
        int ux = x + dx[i], uy = y + dy[i];
        res += check(ux,uy);
    }
    return res;
}

void dfs(int x,int y,int k = 1){
    t[x][y] = k;
    if(k == 64){
        for(int i = 1; i <= 8; i++)
            for(int j = 1; j <= 8; j++)
                cout << t[i][j] << (j == 8 ? '\n' : ' ');
        exit(0);
    }

    vector<array<int, 3>> tmp;
    for(int i = 0; i < 8; i++){
        int ux = x + dx[i] , uy = y + dy[i];
        if(!check(ux,uy)) continue;
        int c = cnt(ux,uy);
        tmp.push_back({c, ux, uy});
    }
    
    sort(all(tmp));
    for (auto a : tmp) {
        dfs(a[1], a[2], k + 1);
        t[a[1]][a[2]] = 0;
    }
}
 
signed main(void){
    cin >> x >> y;
    dfs(y,x);
}
