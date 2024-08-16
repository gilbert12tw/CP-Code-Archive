#include<bits/stdc++.h>
#include<bits/extc++.h>
#define endl '\n'
#define loli
using namespace __gnu_pbds;
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

int n, d;
vector<int> player[2];

int check(int x) {
    for (int i = 1; i < SZ(player[0]); i++) {

    }
    return 1;
}
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
inline void solve() {
    cin >> n >> d;
    vector<int>v(n+1);
    hash_map<int,char>mp;
    for(int i = 1;i<=n;++i){
        char c;cin>>c;
        cin>>v[i];
        mp[v[i]] = c;
    }
    mp[0] = 'R',mp[d] = 'R';
    int l = 0,r = d,ans = d;
    auto check = [&](int m){
        set<int>st;
        for(int i = 1;i<=n;++i){
            st.insert(v[i]);
        }
        st.insert(d);
        int now;
        now = 0;
        int t = 15;
        while(now!=d and t--){
            auto ite = st.upper_bound(now+m);
            if(ite==st.begin()){
                return 0;
            }
            ite--;
            if(*ite==now){
                return 0;
            }
            now = *ite;
            if(mp[now]=='I')st.erase(st.find(now));
        }
        st.erase(st.find(d));
        st.insert(0);
        now = d;
        t = 15;
        while(now!=0 and t--){
            auto ite = st.lower_bound(now-m);
            if(ite==st.end() || *ite==now){
                return 0;
            }
            now = *ite;
            if(mp[now]=='I')st.erase(st.find(now));
        }
        return 1;
    };
    while(l<=r){
        int m = (l+r)>>1;
        if(check(m)){
            ans = m;
            r = m-1;
        }
        else{
            l = m+1;
        }
    }
    cout<<ans<<endl;
}

signed main() {
	//IO;	
    int T; cin >> T;
	while (T--) solve();	
}
