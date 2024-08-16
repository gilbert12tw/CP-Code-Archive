#include<bits/stdc++.h>
#define loli
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
                for (int j = 0; j < c; j++) {
                    tmp.m[i][j] += s * a.m[k][j] % mod;
                    if (tmp.m[i][j] >= mod)
                        tmp.m[i][j] %= mod;
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
	bool inverse(){
		Matrix t(r,r+c);
		for(int y=0;y<r;y++){
			t.m[y][c+y] = 1;
			for(int x=0;x<c;++x)
				t.m[y][x]=m[y][x];
		}
		if( !t.gas() )
			return false;
		for(int y=0;y<r;y++)
			for(int x=0;x<c;++x)
				m[y][x]=t.m[y][c+x]/t.m[y][y];
		return true;
	}
	T gas(){
		vector<T> lazy(r,1);
		bool sign=false;
		for(int i=0;i<r;++i){
			if( m[i][i]==0 ){
				int j=i+1;
				while(j<r&&!m[j][i])j++;
				if(j==r)continue;
				m[i].swap(m[j]);
				sign=!sign;
			}
			for(int j=0;j<r;++j){
				if(i==j)continue;
				lazy[j]=lazy[j]*m[i][i];
				T mx=m[j][i];
				for(int k=0;k<c;++k)
					m[j][k]=m[j][k]*m[i][i]-m[i][k]*mx;
			}
		}
		T det=sign?-1:1;
		for(int i=0;i<r;++i){
			det = det*m[i][i];
			det = det/lazy[i];
			for(auto &j:m[i])j/=lazy[i];
		}
		return det;
	}
};

struct auto_AC_machine {
	static const int mxN = 1000 + 5;
	int trie[mxN][26], ed[mxN], fail[mxN], dp[mxN], tot; 
	inline int insert(string &s) {
		int u = 0;
		for(auto i : s) {
			if(!trie[u][i - 'A']) trie[u][i - 'A'] = ++tot;
			u = trie[u][i - 'A'];
		}
		ed[u]++;
		return u;
	}
	 
	int topo[mxN], tp;
	inline void build() {
		queue<int> q; q.push(0);
		tp = 0;
		while(!q.empty()) {
			int u = q.front(); q.pop();
			topo[tp++] = u;
			for(int i = 0; i < 26; i++) {
				int &to = trie[u][i];
				if(to) {
					fail[to] = (u == 0 ? 0 : trie[fail[u]][i]);	
					q.push(to);
				} else to = trie[fail[u]][i];
			}
		}
	}
} AC;

ll fp(ll a, ll b, ll p) {
	ll res = 1;
	while (b) {
		if (b & 1) res = res * a % p;
		a = a * a % p;
		b >>= 1;
	}
	return res;
}

inline void solve() {
    int n; cin >> n;
    string s; cin >> s;
    AC.insert(s);
    AC.build();

    int m = SZ(s);
    Matrix<int> trans(m, m);
    for (int i = 0; i < AC.tot; i++) {
        for (int j = 0; j < 26; j++) {
            if (AC.trie[i][j] != AC.tot) 
                trans[i][AC.trie[i][j]]++;
        }
    }

    trans = trans ^ n;

    int ans = fp(26, n, mod);
    for (int i = 0; i < m; i++) {
        ans = (ans - trans[0][i]) % mod;
        if (ans < 0) ans += mod;
    }
    cout << ans << '\n';
}

signed main() {
	IO;	
	solve();	
}
