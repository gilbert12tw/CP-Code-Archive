#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
#define int ll
#define pii pair<int,int>
#define f first
#define s second
#define vi vector<int>
#define pb push_back
#define ALL(x) x.begin(),x.end()
#define SZ(x) ((int)x.size())
#define IO ios::sync_with_stdio(false); cin.tie(NULL);

const ll NINF = LLONG_MIN/4;
const ll MAXR = 1000000001LL;

int n;
vector<ll> W, A, dp;
vector<vector<pair<int,int>>> g;
vector<bool> removed;
vector<int> sz;

void get_sz(int u,int p){
    sz[u]=1;
    for(auto& pr:g[u]){
        int v=pr.f;
        if(v==p||removed[v]) continue;
        get_sz(v,u);
        sz[u]+=sz[v];
    }
}

int get_centroid(int u,int p,int tot){
    for(auto& pr:g[u]){
        int v=pr.f;
        if(v!=p&&!removed[v]&&sz[v]>tot/2)
            return get_centroid(v,u,tot);
    }
    return u;
}

void collect(int u,int p,ll d,vector<pair<int,ll>>& vec){
    vec.pb({u,d});
    for(auto& pr:g[u]){
        int v=pr.f,w=pr.s;
        if(v==p||removed[v]) continue;
        collect(v,u,d+w,vec);
    }
}

struct LiChao {
    struct Line{ ll m,b; Line(ll _m=0,ll _b=NINF):m(_m),b(_b){} };
    struct Node{ Line ln; Node *l,*r; Node(Line _ln):ln(_ln),l(nullptr),r(nullptr){} };
    Node* root; ll lo,hi;
    LiChao(ll _lo,ll _hi):root(nullptr),lo(_lo),hi(_hi){}
    ll eval(const Line& f,ll x)const{return f.m*x+f.b;}
    void insert(Line nw){ insert(root,lo,hi,nw); }
    void insert(Node*& nd,ll l,ll r,Line nw){
        if(!nd){ nd=new Node(nw); return; }
        ll mid=(l+r)>>1;
        bool lef=eval(nw,l)>eval(nd->ln,l);
        bool midv=eval(nw,mid)>eval(nd->ln,mid);
        if(midv) swap(nw,nd->ln);
        if(r-l==1) return;
        if(lef!=midv) insert(nd->l,l,mid,nw);
        else insert(nd->r,mid,r,nw);
    }
    ll query(ll x)const{ return query(root,lo,hi,x); }
    ll query(Node* nd,ll l,ll r,ll x)const{
        if(!nd) return NINF;
        ll res=eval(nd->ln,x);
        if(r-l==1) return res;
        ll mid=(l+r)>>1;
        if(x<mid) return max(res,query(nd->l,l,mid,x));
        else return max(res,query(nd->r,mid,r,x));
    }
};

void decompose(int u){
    get_sz(u,-1);
    int c=get_centroid(u,-1,sz[u]);
    removed[c]=true;
    vector<vector<pair<int,ll>>> groups;
    for(auto& pr:g[c]){
        int v=pr.f,w=pr.s;
        if(removed[v]) continue;
        vector<pair<int,ll>> vec;
        collect(v,c,w,vec);
        groups.pb(move(vec));
    }
    LiChao lf(0,MAXR), lb(0,MAXR);
    lf.insert({W[c],A[c]});
    dp[c]=max(dp[c],A[c]);
    for(auto& grp:groups){
        for(auto& pr:grp){
            int x=pr.f; ll d=pr.s;
            dp[x]=max(dp[x],lf.query(d));
        }
        for(auto& pr:grp){
            int y=pr.f; ll d=pr.s;
            lf.insert({W[y],A[y]+W[y]*d});
        }
    }
    dp[c]=max(dp[c],lf.query(0));
    lb.insert({W[c],A[c]});
    for(int i=SZ(groups)-1;i>=0;i--){
        auto& grp=groups[i];
        for(auto& pr:grp){
            int x=pr.f; ll d=pr.s;
            dp[x]=max(dp[x],lb.query(d));
        }
        for(auto& pr:grp){
            int y=pr.f; ll d=pr.s;
            lb.insert({W[y],A[y]+W[y]*d});
        }
    }
    for(auto& pr:g[c]){
        int v=pr.f;
        if(!removed[v]) decompose(v);
    }
}

inline void solve(){
    cin>>n;
    W.assign(n+1,0);
    A.assign(n+1,0);
    for(int i=1;i<=n;i++) cin>>W[i];
    for(int i=1;i<=n;i++) cin>>A[i];
    g.assign(n+1,{});
    for(int i=1;i<n;i++){
        int u,v,l;
        cin>>u>>v>>l;
        g[u].pb({v,l});
        g[v].pb({u,l});
    }
    removed.assign(n+1,false);
    sz.assign(n+1,0);
    dp.assign(n+1,NINF);
    decompose(1);
    ll ans=LLONG_MAX;
    for(int i=1;i<=n;i++) ans=min(ans,dp[i]);
    cout<<ans;
}

signed main(){
    IO;
    solve();
    return 0;
}
