#include<bits/stdc++.h>
//#define loli
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
void abc() {cout << endl;}
template <typename T, typename ...U> void abc(T a, U ...b) {
    cout << a << ' ', abc(b...);
}
#ifdef loli
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
	int r,c; mt m;
	Matrix(int r,int c):r(r),c(c),m(r,rt(c)){}
    Matrix(mt &m_): m(m_) {
        r = m.size(); c = m[0].size();
    }
	rt& operator[](int i){return m[i];}
	matrix operator+(const matrix &a){
		matrix rev(r,c);
		for(int i=0;i<r;++i)
			for(int j=0;j<c;++j)
				rev[i][j]=m[i][j]+a.m[i][j];
		return rev;
	}
	matrix operator-(const matrix &a){
		matrix rev(r,c);
		for(int i=0;i<r;++i)
			for(int j=0;j<c;++j)
				rev[i][j]=m[i][j]-a.m[i][j];
		return rev;
	}
	matrix operator*(const matrix &a){
		matrix tmp(a.c,a.r); int s;
        for (int i = 0; i < r; i++) 
            for (int k = 0; k < c; k++) {
                s = m[i][k];
                for (int j = 0; j < a.c; j++) {
                    tmp.m[i][j] += s * a.m[k][j];
                }
            }
		return tmp;
	}
    matrix operator^(long long b) {
        matrix a(m), res(r, c);
        bool first = 1;
        while (b) {
            if (b&1) {
                if (first) res = a;
                else res = res * a;
                first = 0;
            }
            a = a * a; b >>= 1;
        }
        return res;
    }
    void print() {
        cout << '\n';
        for (int i=0; i<r; i++) {
            cout<<"[";
            for (int j=0; j<c; j++)
                cout<<m[i][j]<<" ]"[j==c-1];
            cout<<"\n";
        }
        cout << '\n';
    }
};


// ax+ny = 1, ax+ny == ax == 1 (mod n)
void exgcd(int x,int y,int &g,int &a,int &b) {
  if (y == 0) g=x,a=1,b=0;
  else exgcd(y,x%y,g,b,a),b-=(x/y)*a;
}

inline void solve() {
    int k; cin >> k;
    // mx -> 44
    vector<vector<int>> inm = {{1, 1}, {1, 0}};
    Matrix<int> res(inm), mat(inm);

    int ans = 0;
    for (int i = 0; i < 50; i++) {
        int x = res[0][0], y = res[0][1]; 
        int g, a, b;
        exgcd(x, y, g, a, b);
        //test(i, x, y, g, a, b);
        //res.print();
        if (k % g == 0) {
            a *= (k / g);
            b *= (k / g);
            int da = y / g;
            int db = x / g;
            if (a <= 0) {
                int k = (-a - da + 1) / da;
                a += da * k;
                b -= db * k;
            }
            if (b <= 0) {
                int k = (-b - db + 1) / db;
                b += db * k;
                a -= da * k;
            }
            while (b < 0) b += db, a -= da;
            while (a < 0) a += da, b -= db;
            //test(i, x, y, a, b);
            if (a >= 0 && b >= 0) {
                test(i, y, a, b, da, db);
                ans = (ans + ((a + da - 1) / da) + ((b + db - 1) / db) - 1) % mod;
            }
            test(ans);
        }
        res = mat * res;
    }
    cout << ans << '\n';
}

signed main() {
	IO;	
	solve();	
}
