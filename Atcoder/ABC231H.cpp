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

class MiniCostMaxiFlow{
  using CapT = int;
  using WeiT = int64_t;
  using PCW = pair<CapT,WeiT>;
  static constexpr CapT INF_CAP = 1 << 30;
  static constexpr WeiT INF_WEI = 1LL<<60;
private:
  struct Edge{
    int to, back;
    WeiT wei;
    CapT cap;
    Edge() {}
    Edge(int a,int b,WeiT c,CapT d):
      to(a),back(b),wei(c),cap(d)
    {}
  };
  int ori, edd;
  vector<vector<Edge>> G;
  vector<int> fa, wh;
  vector<bool> inq;
  vector<WeiT> dis;
  PCW SPFA(){
    fill(inq.begin(),inq.end(),false);
    fill(dis.begin(),dis.end(),INF_WEI);
    queue<int> qq; qq.push(ori);
    dis[ori]=0;
    while(!qq.empty()){
      int u=qq.front();qq.pop();
      inq[u] = 0;
      for(int i=0;i<SZ(G[u]);++i){
        Edge e=G[u][i];
        int v=e.to;
        WeiT d=e.wei;
        if(e.cap<=0||dis[v]<=dis[u]+d)
          continue;
        dis[v]=dis[u]+d;
        fa[v]=u,wh[v]=i;
        if(inq[v]) continue;
        qq.push(v);
        inq[v]=1;
      }
    }
    if(dis[edd]==INF_WEI)
      return {-1,-1};
    CapT mw=INF_CAP;
    for(int i=edd;i!=ori;i=fa[i])
      mw=min(mw,G[fa[i]][wh[i]].cap);
    for (int i=edd;i!=ori;i=fa[i]){
      auto &eg=G[fa[i]][wh[i]];
      eg.cap-=mw;
      G[eg.to][eg.back].cap+=mw;
    }
    return {mw,dis[edd]};
  }
public:
  void init(int a,int b,int n){
    ori=a,edd=b;
    G.clear();G.resize(n);
    fa.resize(n);wh.resize(n);
    inq.resize(n); dis.resize(n);
  }
  void add_edge(int st,int ed,WeiT w,CapT c){
    G[st].emplace_back(ed,SZ(G[ed]),w,c);
    G[ed].emplace_back(st,SZ(G[st])-1,-w,0);
  }
  PCW solve(){
    /* might modify to
    cc += ret.first * ret.second
    or
    ww += ret.first * ret.second
    */
    CapT cc=0; WeiT ww=0;
    while(true){
      PCW ret=SPFA();
      if(ret.first==-1) break;
      test(ret.second);
      cc+=ret.first;
      ww += ret.second;
    }
    return {cc,ww};
  }
} mcmf;

inline void solve() {
    int h, w, n;
    cin >> h >> w >> n;
    int s = 0, t = h + w + 1;
    mcmf.init(s, t, h + w + 5);
    for (int i = 1; i <= n; i++) {
        int a, b, c;
        cin >> a >> b >> c;
        mcmf.add_edge(a, h + b, c, 1);
    }

    for (int i = 1; i <= h; i++) 
        mcmf.add_edge(s, i, 0, 1);
    for (int i = h+1; i <= h + w; i++) 
        mcmf.add_edge(i, t, 0, 1);
    
    auto ans = mcmf.solve();
    cout << ans.S;
}

signed main() {
	IO;	
	solve();	
}
