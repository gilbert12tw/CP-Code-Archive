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
#define mod 998244353
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

/*
2615053605667*(2^18)+1,3
15*(2^27)+1,31
479*(2^21)+1,3
7*17*(2^23)+1,3
3*3*211*(2^19)+1,5
25*(2^22)+1,3
*/
template<typename T,typename VT=vector<T> >
struct NTT{
	const T P,G;
	NTT(T p=998244353,T g=3):P(p),G(g){}
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
	void ntt(bool is_inv,const VT &in,VT &out,int N){
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
    void ntt(bool is_inv,VT &in,int N){
        VT out(SZ(in));
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
        in = out;
	}

    VT convolution(VT &a, VT &b, int len) {
        //a.resize(len); b.resize(len);
        vector<int> d1(len), d2(len), c(len), res(len);
        ntt(false, a, d1, len); ntt(false, b, d2, len);
        for (int i = 0; i < len; i++) c[i] = d1[i] * d2[i] % P;
        ntt(true, c, res, len); 
        return res;
    }
};

vector<int> add(const vector<int> &a, const vector<int> &b) {
    vector<int> res(max(SZ(a), SZ(b)));
    for (int i = 0; i < SZ(res); i++) {
        res[i] = (a[i] + b[i]) % mod;
    }
    return res;
}

const int mxN = 1e6 + 5;
int n, J[mxN], invJ[mxN];
int fp(int a, int b, int p) {
    int res = 1;
    while(b) {
        if(b&1) res = (res * a) % p;
        a = a * a % p;
        b >>= 1;
    }
    return res;
}
void build(int n) {
    J[1] = J[0] = invJ[1] = invJ[0] = 1;
    for(int i = 2; i <= n; i++) J[i] = J[i - 1] * i % mod;
    invJ[n] = fp(J[n], mod - 2, mod);
    for(int i = n - 1; i >= 2; i--) invJ[i] = invJ[i + 1] * (i + 1) % mod;
}
int C(int n, int m) {
	if (n < m) return 0;
    if(n == m or m == 0) return 1;
    int res = J[n] * invJ[n - m] % mod * invJ[m] % mod;
    return res;
}

inline void solve() {
    NTT<int> ntt;
    int n, m;
    cin >> n >> m;
    vector<int> cnt(10 + 1);
    for (int i = 0; i < n; i++) {
        int x; cin >> x;
        cnt[x]++;
    }

    int len = 1<<(__lg(max(m, n * 10)) + 1);
    
    vector<int> odd(len), even(len);
    even[0] = 1;
    ntt.ntt(false, even, len);
    ntt.ntt(false, odd, len);
    for (int i = 1; i <= 10; i++) {
        vector<int> new_odd(len), new_even(len);
        for (int j = 0; j <= cnt[i] && j * i < len; j += 2) {
            new_even[j * i] = C(cnt[i], j);
        }
        for (int j = 1; j <= cnt[i] && j * i < len; j += 2) {
            new_odd[j * i] = C(cnt[i], j);
        }
        ntt.ntt(false, new_even, len);
        ntt.ntt(false, new_odd, len);
        for (int i = 0; i < len; i++) {
            int e = (even[i] * new_even[i] % mod + odd[i] * new_odd[i] % mod) % mod;
            int o = (even[i] * new_odd[i] % mod + odd[i] * new_even[i] % mod) % mod;
            even[i] = e;
            odd[i] = o;
        }
    }
    ntt.ntt(true, odd, len);
    cout << odd[m] << '\n';
}

signed main() {
	IO;	
    build(1000000);
	solve();	
}
