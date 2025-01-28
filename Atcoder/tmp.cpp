#include <bits/stdc++.h>
using namespace std;
#define int long long
#define pii pair<int, int>
#define f first
#define s second
#define mp(x, y) make_pair(x, y)
const int mod = 1e9+7;
const int mxn = 2e5+10;
mt19937 ran(1220);
const int mxN = 1e6 + 5;
int ranking[mxn];

struct Treap {
    struct Node {
        int pri, sum, val, tsz, tag;
        //priority, 子樹和, 值, 子樹大小, 懶標
        int ls, rs, pa;//左子節點, 右子節點, 父節點
        Node(): ls(0), rs(0), pa(0) {}
        Node(int _val): pri(ran()), sum(_val), val(_val), tsz(1), tag(0), ls(0), rs(0), pa(0) {}
    };
    Node nodes[mxN];
    int tot = 0;

#define lc(x) (nodes[x].ls)
#define rc(x) (nodes[x].rs)

    int new_node(int val) {
        nodes[++tot] = Node(val);
        return tot;
    }

    void up(int rt) {
        nodes[rt].sum = nodes[lc(rt)].sum + nodes[rc(rt)].sum + nodes[rt].val;
        nodes[rt].tsz = nodes[lc(rt)].tsz + nodes[rc(rt)].tsz + 1;
        if (lc(rt) != 0) nodes[lc(rt)].pa = rt;
        if (rc(rt) != 0) nodes[rc(rt)].pa = rt;
        nodes[rt].pa = 0;
    }

    void push_tag(int rt) { //打上懶標
        if (!rt) return;
        nodes[rt].tag ^= 1;
    }

    void down(int rt) {//下推懶標
        if (nodes[rt].tag) {
            swap(lc(rt), rc(rt));
            push_tag(lc(rt));
            push_tag(rc(rt));
            nodes[rt].tag = 0;
        }
    }

    int merge(int a, int b) {
        if (!a || !b) return (a + b);
        if (nodes[a].pri < nodes[b].pri) { // a is root
            down(a);
            rc(a) = merge(rc(a), b);
            up(a);
            return a;
        } else { // b is root
            down(b);
            lc(b) = merge(a, lc(b));
            up(b);
            return b;
        }
    }

    // split by size
    void split_bysize(int root, int k, int &a, int &b) {
        if (!root) {
            a = b = 0;
            return;
        }
        down(root);
        if (nodes[lc(root)].tsz + 1 <= k) {
            a = root;
            split_bysize(rc(root), k - (nodes[lc(root)].tsz + 1), rc(a), b);
        } else {
            b = root;
            split_bysize(lc(root), k, a, lc(b));
        }
        up(root);
    }

    int get_rank(int u){
        get(u);

        int p = nodes[u].pa, sum = nodes[lc(u)].tsz + 1;
        while(p){
            if(nodes[p].rs == u) sum += (nodes[lc(p)].tsz + 1); // 向左上爬->加上左子樹
            u = p;//往上爬
            p = nodes[p].pa;//更新為爬完後的父節點
        }
        return sum;
    }

    void get(int u){
        vector<int> tmp;
        while(u) {
            tmp.push_back(u);
            u=nodes[u].pa;
        }
        reverse(tmp.begin(), tmp.end());
        for (int i : tmp) down(i);
    }

    void print(int u) {
        if (u == 0) return;
        print(lc(u));
        cout<<nodes[u].val<<' ';
        print(rc(u));
    }
};

Treap tp;


signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    int n;
    vector<pii>ans;
    cin>>n;
    int root = 0;
    for(int i=1;i<=n;i++){
        int k;
        cin>>k;
        ranking[k] = i;
        root = tp.merge(root, tp.new_node(k));
    }
    for(int i=1;i<=n;i++){


        int l=i, r=tp.get_rank(ranking[i]);
        int x, y, z;
        if(l == r) continue;
        ans.emplace_back(make_pair(l, r));
        tp.split_bysize(root, r, y, z);
        tp.split_bysize(y, l-1, x, y);
        tp.push_tag(y);
        root = tp.merge(x, tp.merge(y, z));
    }
    cout<<ans.size()<<'\n';
    for(auto a:ans)cout<<a.f<<' '<<a.s<<'\n';
}    
