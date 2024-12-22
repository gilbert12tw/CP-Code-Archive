#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
#define int ll
#define pii pair<int, int>
#define X first
#define Y second
#define F first
#define S second
#define vi vector<int>
#define SZ(a) ((int)a.size())
#define ALL(v) v.begin(), v.end()
#define pb push_back
#define eb emplace_back
#define push emplace
#define lb(x, v) lower_bound(ALL(x), v)
#define ub(x, v) upper_bound(ALL(x), v)
#define re(x) reverse(ALL(x))
#define uni(x) x.resize(unique(ALL(x)) - x.begin())
#define inf 1000000000
#define INF 1000000000000000000
#define mod 1000000007
#define MOD 998244353
#define get_bit(x, y) ((x>>y)&1)
#define mkp make_pair
#define IO ios_base::sync_with_stdio(0); cin.tie(0);
void abc() {cerr << endl;}
template <typename T, typename ...U> void abc(T a, U ...b) {
    cerr << a << ' ', abc(b...);
}
#ifdef debug
#define test(args...) abc("[" + string(#args) + "]", args)
#else
#define test(args...) void(0)
#endif

template<class T> bool ckmin(T& a, const T& b) { return b<a ? a=b, 1 : 0; }
template<class T> bool ckmax(T& a, const T& b) { return a<b ? a=b, 1 : 0; }

int check(int type);
int check_v(int type);
int check_h(int type);
int check_d(int type);

int n = 6, m = 7;
int cc, ff;
vector<string> mat(6);
vector<int> cango(100);

int get(int x, int y) {
    return cango[x * 7 + y];
}

void up(int x, int y) {
    char c = mat[x][y];
    while (++x < n) {
        if (mat[x][y] == c) continue;
        cango[x * 7 + y] = 1;
    }
}

int check_v(int type) {
    int cnt = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j + 3 < m; j++) {
            if (mat[i][j] == mat[i][j+1] && 
                    mat[i][j+1] == mat[i][j+2] && 
                    mat[i][j+2] == mat[i][j+3]) {
                if (type == 0) {
                    up(i, j); up(i, j+1); up(i, j+2); up(i, j+3);
                    if (mat[i][j] == 'C')  cc += (check(1) == 0);
                    else if (mat[i][j] == 'F')  ff += (check(1) == 0);
                    cango = vector<int>(100, 0);
                    test(i, j);
                } else {
                    int res = get(i, j) & get(i, j+1) & get(i, j+2) & get(i, j+3);
                    cnt += res;
                }
            }
        }
    }
    return cnt;
}

int check_h(int type) {
    int cnt = 0;
    for (int i = 0; i + 3 < n; i++) {
        for (int j = 0; j < m; j++) {
            if (mat[i][j] == mat[i+1][j] && 
                    mat[i+1][j] == mat[i+2][j] && 
                    mat[i+2][j] == mat[i+3][j]) {
                if (type == 0) {
                    up(i+3, j);
                    if (mat[i][j] == 'C')  cc += (check(1) == 0);
                    else if (mat[i][j] == 'F')  ff += (check(1) == 0);
                    cango = vector<int>(100, 0);
                } else {
                    int res = get(i, j) & get(i+1, j) & get(i+2, j) & get(i+3, j);
                    cnt += res;
                }
            }
        }
    }
    return cnt;
}


int check_d(int type) {
    int cnt = 0;
    for (int i = 0; i + 3 < n; i++) {
        for (int j = 0; j + 3 < m; j++) {
            if (mat[i][j] == mat[i+1][j+1] && 
                    mat[i+1][j+1] == mat[i+2][j+2] && 
                    mat[i+2][j+2] == mat[i+3][j+3]) {
                if (type == 0) {
                    up(i, j); up(i+1, j+1); up(i+2, j+2); up(i+3, j+3);
                    if (mat[i][j] == 'C')  cc += (check(1) == 0);
                    else if (mat[i][j] == 'F')  ff += (check(1) == 0);
                    cango = vector<int>(100, 0);
                } else {
                    int res = get(i, j) & get(i+1, j+1) & get(i+2, j+2) & get(i+3, j+3);
                    cnt += res;
                }
            }
        }
    }

    for (int i = 0; i + 3 < n; i++) {
        for (int j = 3; j < m; j++) {
            if (mat[i][j] == mat[i+1][j-1] && 
                    mat[i+1][j-1] == mat[i+2][j-2] && 
                    mat[i+2][j-2] == mat[i+3][j-3]) {
                if (type == 0) {
                    up(i, j); up(i+1, j-1); up(i+2, j-2); up(i+3, j-3);
                    if (mat[i][j] == 'C')  cc += (check(1) == 0);
                    else if (mat[i][j] == 'F')  ff += (check(1) == 0);
                    cango = vector<int>(100, 0);
                } else {
                    int res = get(i, j) & get(i+1, j-1) & get(i+2, j-2) & get(i+3, j-3);
                    cnt += res;
                }
            }
        }
    }
    return cnt;
}

int check(int type) {
    return check_v(type) + check_h(type) + check_d(type);
}

inline void solve(int cs) {
    for (int i = 0; i < n; i++) {
        cin >> mat[i];
    }
    cc = 0, ff = 0;
    cango = vector<int>(100);

    check(0);
    test(cc, ff);

    cout << "Case #" << cs << ": ";
    if (cc == 0 && ff == 0) cout << 0 << '\n';
    else if (cc > 0 && ff > 0) cout << "?\n";
    else if (cc > 0) cout << "C\n";
    else if (ff > 0) cout << "F\n";
}

signed main() {
    IO;	
    int T; cin >> T;
    for (int i = 1; i <= T; i++) solve(i);	
}
