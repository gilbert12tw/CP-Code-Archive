#include<bits/stdc++.h>
#define x first
#define y second
#define int long long
using namespace std;
const int dx[] = {1, 0, -1, 0}, dy[] = {0, 1, 0, -1};
 
int a[25], n, ans, total;
 
vector<int> tmp;
int sum = 0;
void print_result() {
    int fst = 1;
    cout << "(";
    for (int i : tmp) {
        if (fst) fst = 0; 
        else cout << " + ";
        cout << i;
    }
    cout << ") = " << sum << '\n';
}

void dfs(int u){
    if(u == n){
        if (sum == 0) return;
        print_result();
        return;
    }
    // 選
    tmp.push_back(a[u]);
    sum += a[u];
    dfs(u + 1);
    // undo 取消操作
    sum -= a[u];
    tmp.pop_back();
    
    // 不選
    dfs(u + 1);
}
 
signed main(void){
    ios_base::sync_with_stdio(0); cin.tie(0);

    cin >> n;
    for(int i = 0; i < n; i++)
        cin >> a[i];

    dfs(0);
}
