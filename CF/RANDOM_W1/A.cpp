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

template<typename T>
struct Matrix {
	using rt = std::vector<T>;
	using mt = std::vector<rt>;
	using matrix = Matrix<T>;
	int n; mt m;
	Matrix(int _n): n(_n), m(n,rt(n, -inf)){}
    Matrix(mt &m_): m(m_) {
        n = m.size();
    }
	rt& operator[](int i){return m[i];}
	matrix operator * (const matrix &a) {
		matrix rev(n);
        for (int k = 0; k < n; k++) {
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < n; j++) {
                    rev[i][j] = max(rev[i][j], m[i][k] + a.m[k][j]);
                    rev[i][j] = max(rev[i][j], m[i][j]);
                    rev[i][j] = max(rev[i][j], a.m[i][j]);
                }
            }
        }
		return rev;
	}
};

inline void solve() {
    int n, m;
    cin >> n >> m;
    Matrix<int> mat(n);
    for (int i = 0; i < m; i++) {
        int a, b, c, d;
        cin >> a >> b >> c >> d;
        a--, b--;
        mat[a][b] = c;
        mat[b][a] = d;
    }

    vector<Matrix<int>> pw_mat;
    pw_mat.eb(mat);
    for (int i = 1; (1<<i) <= n; i++) {
        auto &m =  pw_mat.back();
        pw_mat.eb(m * m);
    }

    auto check_inf = [](Matrix<int> &m) -> bool {
        for (int i = 0; i < m.n; i++) {
            if (m[i][i] > 0) return true;
        }
        return false;
    };

    int ans = 1;
    auto res = mat;
    for (int i = pw_mat.size() - 1; i >= 0; i--) {
        auto &m = pw_mat[i];
        auto new_mat = m * res;
        if (!check_inf(new_mat)) {
            res = move(new_mat);
            ans += (1<<i);
            test(i);
        } 
    }
    res = res * mat;
    if (!check_inf(res)) cout << 0 << '\n';
    else cout << ans + 1 << '\n';
}

signed main() {
	IO;	
	solve();	
}
