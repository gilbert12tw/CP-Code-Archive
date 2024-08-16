
#include<bits/stdc++.h>
#include<bits/extc++.h>
#define loli
using namespace std;
using namespace __gnu_pbds;
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
struct custom_hash {
	static uint64_t splitmix64(uint64_t x) {
		x += 0x9e3779b97f4a7c15;
		x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
		x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
		return x ^ (x >> 31);
	}
	size_t operator()(uint64_t x) const {
		static const uint64_t FIXED_RANDOM = chrono::steady_clock::now().time_since_epoch().count();
		return splitmix64(x + FIXED_RANDOM);
	}
	size_t operator()(pair<uint64_t,uint64_t> x) const {
		static const uint64_t FIXED_RANDOM = chrono::steady_clock::now().time_since_epoch().count();
		return splitmix64(3*x.first + x.second + FIXED_RANDOM);
	}
};
template<class T,class U>using hash_map = gp_hash_table<T,U,custom_hash>;
vector<int>mp(200005);
inline void solve() {
    int n,m,q,flag = 1,cnt = 0;
    cin>>n>>m>>q;
    vector<pair<char,int>>qry(q); 
    for(int i = 0;i<q;++i){
        cin>>qry[i].first>>qry[i].second;
        if(qry[i].second>n){
            if(flag==1){
                cout<<"invalid"<<endl;
                flag = 0;
            }
        }
        mp[qry[i].second] = 0;
    }
    for(int i = 0;i<q;++i){
        auto [c,x] = qry[i];
        if(mp[x]==0)cnt++;
        if(c=='+')mp[x]++;
        else mp[x]--;
        if(mp[x]==0)cnt--;
        if(mp[x]<0 || cnt>m){
            if(flag==1){
                cout<<"invalid"<<endl;
                flag = 0;
            }
        }
    }
    if(flag)
    cout<<"valid"<<endl;
}

signed main() {
	IO;	
    int t;
    cin>>t;
    while(t--){
        solve();	
    }
}
