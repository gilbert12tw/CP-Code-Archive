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
#define get_bit(x, y) ((x>>y)&1)
#define mkp make_pair
#define IO ios_base::sync_with_stdio(0); cin.tie(0);
void abc() {cout << endl;}
template <typename T, typename ...U> void abc(T a, U ...b) {
    cout << a << ' ', abc(b...);
}
template <typename T> void printv(T l, T r) {
    for (; l != r; ++l) cout << *l << " \n"[l + 1 == r];
}
template <typename A, typename B> istream& operator >> (istream& o, pair<A, B> &a) {
    return o >> a.X >> a.Y;
}
template <typename A, typename B> ostream& operator << (ostream& o, pair<A, B> a) {
    return o << '(' << a.X << ", " << a.Y << ')';
}
template <typename T> ostream& operator << (ostream& o, vector<T> a) {
    bool is = false;
    if (a.empty()) return o << "{}";
    for (T i : a) {o << (is ? ' ' : '{'), is = true, o << i;}
    return o << '}';
}
#ifdef loli
#define test(args...) abc("[" + string(#args) + "]", args)
#else
#define test(args...) void(0)
#endif

const int mxN = 2e6 + 5;

struct PT {
	int x,y;
	PT(){}
	PT(const int&x,const int&y):x(x),y(y){}
	PT operator+(const PT &b)const{
		return PT(x+b.x,y+b.y);
	}
	PT operator-(const PT &b)const{
		return PT(x-b.x,y-b.y);
	}
	PT operator*(const int &b)const{
		return PT(x*b,y*b);
	}
	PT operator/(const int &b)const{
		return PT(x/b,y/b);
	}
	bool operator==(const PT &b)const{
		return x==b.x&&y==b.y;
	}
	int dot(const PT &b)const{
		return x*b.x+y*b.y;
	}
	int cross(const PT &b)const{
		return x*b.y-y*b.x;
	}
	int abs2()const{//向量長度的平方
		return dot(*this);
	}
};

bool btw(const PT &p1, const PT &p2, const PT &p3) {
    if ((p1 - p2).cross(p3 - p2) == 0 &&
        min(p1.x, p3.x) <= p2.x && p2.x <= max(p1.x, p3.x) &&
        min(p1.y, p3.y) <= p2.y && p2.y <= max(p1.y, p3.y)) return 1;
    return 0;
}


int point_in_convex(const vector<PT> &ConvexHull, const PT &p) {
  int l = 0, r = (int)ConvexHull.size() - 1;
  int n = SZ(ConvexHull);
  while (l <= r) {
    int m = (l + r) / 2;
    auto a1 = (ConvexHull[m] - ConvexHull[0]).cross(p - ConvexHull[0]);
    auto a2 = (ConvexHull[(m + 1) % n] - ConvexHull[0]).cross(p - ConvexHull[0]);
    if (a1 >= 0 && a2 <= 0) {
      auto res = (ConvexHull[(m + 1) % n] - ConvexHull[m]).cross(p - ConvexHull[m]);
      return res > 0 ? 1 : (res >= 0 ? -1 : 0);
    }
    if (a1 < 0) r = m - 1;
    else l = m + 1;
  }
  return 0;
}



inline void solve() {
    int n;
    vector<PT> cvx;
    cin >> n;
    for (int i = 0; i < n; i++) {
        PT tmp;
        cin >> tmp.x >> tmp.y;
        cvx.eb(tmp);
    }
    int q; cin >> q;
    while (q--) {
        PT tmp;
        cin >> tmp.x >> tmp.y;
        int ans = point_in_convex(cvx, tmp); 
        if (ans == 1 && btw(cvx[0], tmp, cvx[1])) cout << "ON\n";
        else if (ans == 1 && btw(cvx[0], tmp, cvx.back())) cout << "ON\n";
        else if (ans == 0) cout << "OUT\n";
        else if (ans == 1) cout << "IN\n";
        else cout << "ON\n";
    }
}

signed main() {
	IO;	
	solve();	
}
