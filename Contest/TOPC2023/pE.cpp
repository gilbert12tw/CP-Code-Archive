#include <bits/stdc++.h>
#pragma GCC optimize("O2")
using namespace std;

typedef pair<int, int> pii;
typedef long long ll;
typedef unsigned long long ull;
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
#define SZ(_a) (_a).size()
const ll INF = 1e14;

__int128 a, b, m;

struct Matrix{
    vector<vector<__int128> > M;
    Matrix () {
        M.resize(2);
        for (int i = 0;i < 2; ++i)
            M[i].resize(2);
        M[0][0] = 0;
        M[0][1] = 0;
        M[1][0] = 0;
        M[1][1] = 0;
    }
    Matrix operator * (Matrix B) {
        vector<vector<__int128> > buf;
        buf.resize(2);
        for (int i = 0;i < 2; ++i) buf[i].resize(2);

        for (int i = 0;i <2; ++i)
            for (int j = 0;j <2; ++j)
                for (int k = 0;k <2; ++k)
                    buf[i][j] += M[i][k]*B.M[k][j]%m;
        
        Matrix C;
        for (int i = 0;i < 2; ++i)
            for (int j = 0;j < 2; ++j)
                C.M[i][j] = buf[i][j] % m;
        return C;
    }
};

Matrix solve(ull b) {
    if (b == 1) {
        Matrix ret;
        ret.M[0][0] = a;
        ret.M[0][1] = m-1;
        ret.M[1][0] = 1;
        ret.M[1][1] = 0;
        return ret;
    }
    if (b&1) {
        Matrix tmp = solve(b/2);
        Matrix base;
        base.M[0][0] = a;
        base.M[0][1] = m-1;
        base.M[1][0] = 1;
        base.M[1][1] = 0;
        return (tmp*tmp)*base;
    } else {
        Matrix tmp = solve(b/2);
        return tmp*tmp;
    }
}

__int128 get(string s) {
    __int128 ret = 0;
    for (int i = 0;i < SZ(s); ++i)
        ret = ret * 10 + s[i]-'0';
    return ret;
}

void outputint(__int128 tmp){
    if (tmp == 0) {
        cout << "0\n";
        return ;
    }
    string s = "";
    while (tmp > 0) s.pb('0'+tmp%10), tmp /= 10;
    reverse(s.begin(), s.end());
    cout << s << "\n";
}

int main(){
    string s;
    cin >> s;
    a = get(s);
    cin >> s;
    b = get(s);
    cin >> s;
    m = get(s);
    a %= m;
    if (b == 1) {
        outputint(a);
        return 0;
    }
    // ll cur = a;
    // mp[1] = a;
    // for(ll i = 2, j = 2; j < 64; i *= 2LL, j++){
    //     mp[i] = cur * cur - 2;
    //     cur = mp[i];
    // }
    Matrix mans = solve(b-1);
    __int128 tmp = mans.M[0][0]*a%m + mans.M[0][1]*2%m;
    tmp = (tmp %m + m) % m;
    outputint(tmp);
    return 0;
}


