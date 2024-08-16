#include <set>
#include <map>
#include <deque>
#include <queue>
#include <stack>
#include <cmath>
#include <ctime>
#include <bitset>
#include <cstdio>
#include <string>
#include <vector>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

typedef long long LL;
typedef pair<LL, LL> pLL;
typedef pair<LL, int> pLi;
typedef pair<int, LL> pil;;
typedef pair<int, int> pii;
typedef unsigned long long uLL;
#define lson l,mid,rt<<1
#define rson mid+1,r,rt<<1|1
#define bug printf("*********\n")
#define IO ios::sync_with_stdio(false),cin.tie(0)
#define debug1(x) cout<<"["<<#x<<" "<<(x)<<"]\n"
#define debug2(x,y) cout<<"["<<#x<<" "<<(x)<<" "<<#y<<" "<<(y)<<"]\n"
#define debug3(x,y,z) cout<<"["<<#x<<" "<<(x)<<" "<<#y<<" "<<(y)<<" "<<#z<<" "<<z<<"]\n"
LL read() {
    int x = 0, f = 1; char ch = getchar();
    while(ch < '0' || ch > '9') {
        if(ch == '-')f = -1;
        ch = getchar();
    }
    while(ch >= '0' && ch <= '9') {
        x = x * 10 + ch - '0';
        ch = getchar();
    }
    return x * f;
}
const double eps = 1e-8;
const int mod = 1e9 + 7;
const int maxn = 3e5 + 5;
const int INF = 0x3f3f3f3f;
const LL INFLL = 0x3f3f3f3f3f3f3f3f;
int n;
int num;
vector<pii> aa;
vector<int> a;
vector<int> b;
int get_ans() {
    vector<int> tmpa;
    tmpa = a;
    vector<int> tmpb;
    tmpb = b;
    sort(tmpa.begin(), tmpa.end());
    sort(tmpb.begin(), tmpb.end());
    int ans = 0;
    int tmp = 0;
    for(int i = 0; i < n; i++) {
        if(tmp == n) break;
        if(tmpa[tmp] < tmpb[i]) {
            ans++;
            tmp++;
        }
    }
    return ans;
}
int len;
bool check(int pos, int mid) {
    int res = 0;
    int tmp = 0;
    for(int i = 0; i < len; i++) {
        if(i == mid) continue;
        if(tmp == n) continue;
        while(tmp < n && aa[tmp].second <= pos) tmp++;
        if(aa[tmp].first < b[i]) tmp++, res++;
    }
    if(res == num) return 1;
    else {
        if(res + (b[mid] > a[pos]) == num) return 1;
        else if(res + (b[len - 1] > a[pos]) == num) return 1;
        else return 0;
    }
}
int main() {
    scanf("%d", &n);
    for(int i = 0, x; i < n; i++) {
        scanf("%d", &x);
        a.push_back(x);
        aa.push_back(make_pair(x, i));
    }
    for(int i = 1, x; i <= n; i++) {
        scanf("%d", &x);
        b.push_back(x);
    }
    sort(aa.begin(), aa.end());
    sort(b.begin(), b.end());
    num = get_ans();
    vector<int> ans;
    for(int i = 0; i < n; i++) {
        len = b.size() ;
        int l = 0, r = len - 1;
        while(r - l > 1) {
            int mid = (l + r) >> 1;
            // debug1(num);
            // debug3(l, r, mid);
            if(check(i, mid)) {
                l = mid;
            } else {
                r = mid;
            }
        }
        // debug1(l);
        // debug3(r, (int)check(i, r), num);
        if(check(i, r)) {
            ans.push_back(b[r]);
            num -= a[i] < b[r];
            b.erase(b.begin() + r);
        } else {
            ans.push_back(b[l]);
            num -= a[i] < b[l];
            b.erase(b.begin() + l);
        }
    }
    for(int i = 0; i < ans.size(); i++) {
        printf("%d%c", ans[i], i == ans.size() - 1 ? '\n' : ' ');
    }
    return 0;
}
