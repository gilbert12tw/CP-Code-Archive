#include<bits/stdc++.h>
#include"jngen.h"
using namespace std;
typedef long long ll;
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

void generate_input(int c) {
    string in = to_string(c) + ".in";
    ofstream file;
    file.open (in);

    int n = 1000;
    file << n << '\n';

    file.close();
}

void gen(int st, int ed) {
	for (int i = st; i <= ed; i++) {
		generate_input(i);
	}
	cerr << "Finish Yeh!!!\n";
}

signed main(int argc, char* argv[]) {
    parseArgs(argc, argv);
    int st = getOpt(0);
    int ed = getOpt(1);
    gen(st, ed);
}
