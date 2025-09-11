#include <bits/stdc++.h>
using namespace std;
#define int long long
#define f first
#define s second
#define mp(x, y) make_pair(x, y)
const int mod = 1e9+7;
const int mxn = 2e5+10;

mt19937 ran(1220);
const int mxN = 1e6 + 5;

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

    int get(int u){
        while(nodes[u].pa != 0){
            u = nodes[u].pa;
        }

        return u;
    }

	void up(int rt) {
	    nodes[rt].sum = nodes[lc(rt)].sum + nodes[rc(rt)].sum + nodes[rt].val;
	    nodes[rt].tsz = nodes[lc(rt)].tsz + nodes[rc(rt)].tsz + 1;
	    if (lc(rt) != 0) nodes[lc(rt)].pa = rt;
	    if (rc(rt) != 0) nodes[rc(rt)].pa = rt;
	    nodes[rt].pa = 0;
	}

	void push_tag(int rt, int tg) { //打上懶標
	    if (!rt) return;
	    nodes[rt].tag += tg;
	    nodes[rt].val += tg;
	    nodes[rt].sum += tg * nodes[rt].tsz;
	}

	void down(int rt) {//下推懶標
	    if (nodes[rt].tag) {
	    	push_tag(lc(rt), nodes[rt].tag);
	    	push_tag(rc(rt), nodes[rt].tag);
	    	nodes[rt].tag = 0;
	    }
	}

    int get_rank(int u){
        int p = nodes[u].pa, sum = nodes[lc(u)].tsz + 1;
        while(p){
            if(nodes[p].rs == u) sum += (nodes[lc(p)].tsz + 1); // 向左上爬->加上左子樹
            u = p;//往上爬
            p = nodes[p].pa;//更新為爬完後的父節點
        }
        return sum;
    }

	int merge(int a, int b) {
        if(a == b)return a;
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
	    if (nodes[lc(root)].tsz + 1 <= k) {
	    	a = root;
	    	split_bysize(rc(root), k - (nodes[lc(root)].tsz + 1), rc(a), b);
	    } else {
	    	b = root;
	    	split_bysize(lc(root), k, a, lc(b));
	    }
	    up(root);
	}

	void print(int u) {
	    if (u == 0) return;
	    print(lc(u));
	    //test(u, nodes[u].val, nodes[u].sum, nodes[u].tsz);
	    print(rc(u));
	}
};

Treap tp;

signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    int n, m;
    cin>>n>>m;
    for(int i=1;i<=n;i++){
        int k;
        cin>>k;
        tp.new_node(k);
    }
    while(m--){
        char cmd;
        cin>>cmd;
        if(cmd == 'M'){
            int a, b;
            cin>>a>>b;
            a = tp.get(a);
            b = tp.get(b);
            tp.merge(a, b);
        }
        if(cmd == 'D'){
            int a;
            cin>>a;
            int b = tp.get_rank(a);
            a = tp.get(a);
            int x, y;
            tp.split_bysize(a, b, x, y);

        }
        if(cmd == 'Q'){
            int l, r;
            cin>>l>>r;
            if(tp.get(l)!=tp.get(r)){
                cout << -1 << '\n';
                continue;
            }
            int a, b, c, root = tp.get(l);
            r = tp.get_rank(r);
            l = tp.get_rank(l);
            if (l > r) swap(l, r);
            tp.split_bysize(root, r, b, c);
            tp.split_bysize(b, l-1, a, b);
            cout<<tp.nodes[b].sum<<'\n';
            tp.merge(a, tp.merge(b, c));
        }
    }
}
