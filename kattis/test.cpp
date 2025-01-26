#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <cctype>
#include <algorithm>
#include <functional>
#include <numeric>
#include <string>
#include <set>
#include <map>
#include <stack>
#include <vector>
#include <queue>
#include <deque>
#include <list>

using namespace std;
#define inf 1<<30
#define maxn 3005
map <int,int> mp;
vector <int> vec[maxn];
int dp[maxn];
int val[maxn];
vector <int> ans;
int getnum(int x[], int len, int poi)
{
    int res = 0;
    for (int i = len - 1; i >= 0; i--)
    {
        if (poi & (1 << i)) res = res * 10 + x[i];
    }
    return res;
}
bool Leading_Zero(int x[], int len, int poi)
{
    for (int i = len - 1; i >= 0; i--)
    {
        if (poi & (1 << i))
        {
            if (x[i] == 0) return true;
            return false;
        }
    }
    return true;
}
int solve(int num)
{
    if (dp[num] != -1) return dp[num];  //记忆化搜索

    dp[num] = 0;
    int len = vec[num].size();

    for(int i = 0; i < len; i++)
    {
        dp[num] = max(dp[num], solve(vec[num][i]));
    }

    return ++dp[num];
}
void dfs(int cur)
{
    ans.push_back(val[cur]);

    int len = vec[cur].size();
    if (len == 0) return;

    int minnum = inf,best = 0;
    for (int i = 0; i < len; i++)
    {
        int v = vec[cur][i];
        if (dp[cur] == dp[v] + 1 && val[v] < minnum)
        {
            minnum = val[v];
            best = v;
        }
    }
    dfs(best);
}

int main()
{
    int num;
    while(cin >> num)
    {
        if (num == 0) break;

        memset(dp, -1, sizeof dp);  //记录当前值为i的时候，深度（后面最多能删减几次）
        ans.clear();  //存储答案
        mp.clear();
        for (int i = 0; i < 3000; i++) vec[i].clear();

        if (num < 10) //如果是个位数，无法删，直接输出
        {
            printf("%d\n",num);
            continue;
        }

        int beginnum = num;

        int x[10] = {};
        int n = 0;   //记录位数
        while(num > 0)
        {
            x[n++] = num % 10;
            num /= 10;
        }
        int cnt = 0;
        for (int i = 1; i < (1 << n); i++)
        {
            int u = getnum(x, n, i);  //取出x所有子序列
            if (!mp[u])
            {
                mp[u] = ++cnt;  //离散化，标记数字
                val[cnt] = u;
            }

        }

        for (int i = 1; i < (1 << n); i++)  //遍历x所有的子集
        {
            int u = getnum(x, n, i);  //取出该子集的数字
            if (Leading_Zero(x,n,i)) continue;
            for (int j = (i - 1)&i; j ; j = (j - 1)&i) // 遍历u的所有子集
            {
                if (Leading_Zero(x,n,j)) continue;

                int k = getnum(x, n, j);  //从u中取走的数字
                int v = getnum(x,n,i^j); //从u中取走数字后剩下的值

                if (k <= 1 || u % k) continue;   //如果u不能整除k，即k不是u的约数

                vec[mp[u]].push_back(mp[v]);  //vec[i]表示：当前数字为i的时候，接下来一个取值（满足约数+子串）可以为vec[i][j]
            }
        }

        for(int i = 1; i <= cnt; i++) dp[i] = solve(i);

        dfs(mp[beginnum]);

        printf("%d",ans[0]);
        int len = ans.size();
        for (int i = 1; i < len; i++) printf(" %d",ans[i]);
        printf("\n");
    }
    return 0;
}
