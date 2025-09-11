#include<bits/stdc++.h>
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


// 2615053605667*(2^18)+1,3
// 15*(2^27)+1,31
// 479*(2^21)+1,3
// 7*17*(2^23)+1,3
// 3*3*211*(2^19)+1,5
// 25*(2^22)+1,3
template<typename T,typename VT=vector<T> >
struct NTT{
	const T P,G;
	NTT(T p=(1<<23)*7*17+1,T g=3):P(p),G(g){}
	unsigned bit_reverse(unsigned a,int len){
        a=((a&0x55555555U)<<1)|((a&0xAAAAAAAAU)>>1);
		a=((a&0x33333333U)<<2)|((a&0xCCCCCCCCU)>>2);
		a=((a&0x0F0F0F0FU)<<4)|((a&0xF0F0F0F0U)>>4);
		a=((a&0x00FF00FFU)<<8)|((a&0xFF00FF00U)>>8);
		a=((a&0x0000FFFFU)<<16)|((a&0xFFFF0000U)>>16);
		return a>>(32-len);
	}
	T pow_mod(T n,T k,T m){
		T ans=1;
		for(n=(n>=m?n%m:n);k;k>>=1){
			if(k&1)ans=ans*n%m;
			n=n*n%m;
		}
		return ans;
	}
	void ntt(bool is_inv,VT &in,VT &out,int N){
		int bitlen=__lg(N);
		for(int i=0;i<N;++i)out[bit_reverse(i,bitlen)]=in[i];
		for(int step=2,id=1;step<=N;step<<=1,++id){
			T wn=pow_mod(G,(P-1)>>id,P),wi=1,u,t;
			const int mh=step>>1;
			for(int i=0;i<mh;++i){
				for(int j=i;j<N;j+=step){
					u=out[j],t=wi*out[j+mh]%P;
					out[j]=u+t;
					out[j+mh]=u-t;
					if(out[j]>=P)out[j]-=P;
					if(out[j+mh]<0)out[j+mh]+=P;
				}
				wi=wi*wn%P;
			}
		}
		if(is_inv){
			for(int i=1;i<N/2;++i)swap(out[i],out[N-i]);
			T invn=pow_mod(N,P-2,P);
			for(int i=0;i<N;++i)out[i]=out[i]*invn%P;
		}
	}
    VT convolution(VT a, VT b) {
        int len = 1<<(__lg(SZ(a) + SZ(b)) + 1);
        a.resize(len); b.resize(len);
        vector<int> d1(len), d2(len), c(len), res(len);
        ntt(false, a, d1, len);
        ntt(false, b, d2, len);
        for (int i = 0; i < len; i++) c[i] = d1[i] * d2[i] % P;
        ntt(true, c, res, len);
        return res;
    }
};

inline void solve() {
    int n; cin >> n;
    vector<int> s(n);
    NTT<int> ntt;

    int mx = 0;
    for (int &i : s) {
        cin >> i;
        mx = max(mx, i);
    }

    mx *= 2;
    vector<int> a(mx);
    for (int i : s) a[i]++;

    auto con = ntt.convolution(a, a);
    int ans = 0;
    for (int i = 2; i <= mx; i += 2) {
        //test(i, con[i], a[i / 2]);
        if (a[i / 2]) {
            ans += (con[i] - 1) / 2;
        }
    }
    cout << ans << '\n';
}

signed main() {
	IO;	
	solve();	
}
