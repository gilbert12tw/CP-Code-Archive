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
void suffix_array(const char *s,int n,int *sa,int *rank,int *tmp,int *c){
	int A='z'+1,i,k,id=0;
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
void suffix_array_lcp(const char *s,int len,int *h,int *sa,int *rank){
	for(int i=0;i<len;++i)rank[sa[i]]=i;
	for(int i=0,k=0;i<len;++i){
		if(rank[i]==0)continue;
		if(k)--k;
		while(s[i+k]==s[sa[rank[i]-1]+k])++k;
		h[rank[i]]=k;
	}
	h[0]=0;// h[k]=lcp(sa[k],sa[k-1]);
}

const int mxN = 4e5 + 5;
char s[mxN];
int n;
int h[mxN], sa[mxN], rk[mxN], tmp[mxN], c[mxN];

inline void solve() {
    cin >> s;
    int n = strlen(s);
    suffix_array(s, n, sa, rk, tmp, c);
    suffix_array_lcp(s, n, h, sa, rk);
    cout << n << ' ';
    for (int i = 0; i < n; i++) cout << sa[i] << " \n"[i == n-1];
    for (int i = 0; i < n; i++) cout << h[i] << " \n"[i == n-1];
}

signed main() {
	IO;	
	solve();	
}
