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

#define radix_sort(x,y){\
	for(i=0;i<A;++i)c[i]=0;\
	for(i=0;i<n;++i)c[x[y[i]]]++;\
	for(i=1;i<A;++i)c[i]+=c[i-1];\
	for(i=n-1;~i;--i)sa[--c[x[y[i]]]]=y[i];\
}
#define AC(r,a,b)\
	r[a]!=r[b]||a+k>=n||r[a+k]!=r[b+k]
void suffix_array(const string &s,int *sa,int *rank,int *tmp,int *c){
	int A='z'+1,i,k,id=0,n=s.size();
	for(i=0;i<n;++i)rank[tmp[i]=i]=s[i];
	radix_sort(rank,tmp);
	for(k=1;id<n-1;k<<=1){
		for(id=0,i=n-k;i<n;++i)tmp[id++]=i;
		for(i=0;i<n;++i)
			if(sa[i]>=k)tmp[id++]=sa[i]-k;
		radix_sort(rank,tmp);
		swap(rank,tmp);
		for(rank[sa[0]]=id=0,i=1;i<n;++i)
			rank[sa[i]]=id+=AC(tmp,sa[i-1],sa[i]);
		A=id+1;
	}
}
//h:高度數組 sa:後綴數組 rank:排名 
void suffix_array_lcp(const string &s,int *h,int *sa,int *rank){
    int len = s.size();
	for(int i=0;i<len;++i)rank[sa[i]]=i;
	for(int i=0,k=0;i<len;++i){
		if(rank[i]==0)continue;
		if(k)--k;
		while(s[i+k]==s[sa[rank[i]-1]+k])++k;
		h[rank[i]]=k;
	}
	h[0]=0;// h[k]=lcp(sa[k],sa[k-1]);
}
const int mxL = 5e5 + 5;
int sa[mxL], rk[mxL], tmp[mxL], c[mxL], h[mxL];

inline void solve() {
    string s; cin >> s;
    int k; cin >> k;
    suffix_array(s, sa, rk, tmp, c);    
    suffix_array_lcp(s, h, sa, rk);

    vector<int> stk, nxt(SZ(s)), prv(SZ(s));
    stk.eb(0);
    for (int i = 1; i < SZ(s); i++) {
        test(i, h[i]);
        while (SZ(stk) > 1 && h[stk.back()] >= h[i]) 
            stk.pop_back();
        prv[i] = stk.back();
        stk.eb(i);
    }
    stk.clear(); stk.eb(SZ(s));
    for (int i = SZ(s) - 1; i > 0; i--) {
        while (SZ(stk) > 1 && h[stk.back()] >= h[i]) 
            stk.pop_back();
        nxt[i] = stk.back();
        stk.eb(i);
    }
    int ans = -1;
    h[SZ(s)] = 0;
    if (k == 1) {
        for (int i = 0; i < SZ(s); i++) {
            int len = SZ(s) - sa[i];
            if (h[i] < len && h[i+1] < len) {
                ans = max(len, ans);
            }
        }
    } else {
        for (int i = 1; i < SZ(s); i++) {
            if (nxt[i] - prv[i] == k) {
                if (h[i]) ans = max(ans, h[i]);
            }
        }
    }
    cout << ans << '\n';
}

signed main() {
	IO;	
    int T; cin >> T;
	while (T--) solve();	
}
