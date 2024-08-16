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

// p2 in p1 -> p3
int btw(const PT &p1, const PT &p2, const PT &p3) {
    if ((p1 - p2).cross(p3 - p2) == 0 &&
        min(p1.x, p3.x) <= p2.x && p2.x <= max(p1.x, p3.x) &&
        min(p1.y, p3.y) <= p2.y && p2.y <= max(p1.y, p3.y)) return 1;
    return 0;
}

int sgn(int x) {
    if (x > 0) return 1;
    else if (x == 0) return 0;
    return -1;
}

int inter(const PT &a, const PT &b, const PT &c, const PT &d) {
    if(min(a.y, b.y) <= max(c.y, d.y) and min(c.y, d.y) <= max(a.y, b.y) and
	   min(a.x, b.x) <= max(c.x, d.x) and min(c.x, d.x) <= max(a.x, b.x) and
	   sgn((b - a).cross(c - a)) * sgn((b - a).cross(d - a)) <= 0 and
	   sgn((d - c).cross(a - c)) * sgn((d - c).cross(b - c)) <= 0) return 1;
	return 0;
}


inline void solve() {
    int n;
    cin >> n;
    while (n--) {
        PT p[4]; 
        for (int i = 0; i < 4; i++) {
            cin >> p[i].x >> p[i].y;
        }
        cout << (inter(p[0], p[1], p[2], p[3]) ? "YES\n" : "NO\n");
    }
}

signed main() {
	IO;	
	solve();	
}
