#include<iostream>
#include<vector>
#include<string>
#include<utility>
#include<algorithm>
#include<queue>
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

#define pushS(x) sa[--bkt[s[x]]] = x  
#define pushL(x) sa[bkt[s[x]]++] = x
#define induce_sort(v){\
	fill_n(sa,n,0);\
	copy_n(_bkt,A,bkt);\
	for(i=n1-1;~i;--i)pushS(v[i]);\
	copy_n(_bkt,A-1,bkt+1);\
	for(i=0;i<n;++i)if(sa[i]&&!t[sa[i]-1])pushL(sa[i]-1);\
	copy_n(_bkt,A,bkt);\
	for(i=n-1;~i;--i)if(sa[i]&&t[sa[i]-1])pushS(sa[i]-1);\
}
template<typename T>
void sais(const T s,int n,int *sa,int *_bkt,int *p,bool *t,int A){
	int *rnk=p+n,*s1=p+n/2,*bkt=_bkt+A;
	int n1=0,i,j,x=t[n-1]=1,y=rnk[0]=-1,cnt=-1;
	for(i=n-2;~i;--i)t[i]=(s[i]==s[i+1]?t[i+1]:s[i]<s[i+1]);
	for(i=1;i<n;++i)rnk[i]=t[i]&&!t[i-1]?(p[n1]=i,n1++):-1;
	fill_n(_bkt,A,0);
	for(i=0;i<n;++i)++_bkt[s[i]];
	for(i=1;i<A;++i)_bkt[i]+=_bkt[i-1];
	induce_sort(p);
	for(i=0;i<n;++i)if(~(x=rnk[sa[i]]))
		j=y<0||memcmp(s+p[x],s+p[y],(p[x+1]-p[x])*sizeof(s[0]))
		,s1[y=x]=cnt+=j;
	if(cnt+1<n1)sais(s1,n1,sa,bkt,rnk,t+n,cnt+1);
	else for(i=0;i<n1;++i)sa[s1[i]]=i;
	for(i=0;i<n1;++i)s1[i]=p[sa[i]];
	induce_sort(s1);
}

/*****************這些是需要用到的陣列大小**************/
const int MAXN=10000005, MAXA='z'+1;
int sa[MAXN], bkt[MAXN+MAXA], p[MAXN*2];
bool t[MAXN*2];
char s[MAXN];

inline void solve() {
    int k;
    cin >> s >> k;
    int n = strlen(s);
    s[n] = '#';
    sais(s, n + 1, sa, bkt, p, t, MAXA);

    vector<int> rk(n + 2), lcp(n + 2);
    for (int i = 1; i <= n; i++) 
        rk[sa[i]] = i;

    // LCP
    for (int i = 1, k = 0; i <= n; i++) {
        if (rk[i] == 0) continue;
        if (k) --k;
        while (s[i + k] == s[sa[rk[i] - 1] + k]) ++k;
        lcp[rk[i]] = k;
    }

    int res = 0;
    for (int i = 1; i <= n; i++) {
        test(sa[i]);
        if (res + n - sa[i] < k) {
            res += n - sa[i];
        }
        else {
            int tmp = k - res + lcp[i];
            test(k, tmp);
            for (int j = sa[i]; j < sa[i] + tmp; j++)
                cout << s[j];
            break;
        }
    } 

}

signed main() {
	IO;	
	solve();	
}
