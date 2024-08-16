struct Segment_Tree {
#define ls (x<<1)
#define rs ((x<<1)|1)
#define mid ((l+r)>>1)
    int n;
    vector<int> seg;
    Segment_Tree(int _n): n(_n), seg(_n * 4) {}

    inline int op(int &a, int &b) {
        return a + b;
    }

    void up(int x) {
        seg[x] = op(seg[ls], seg[rs]);
    }

    void build(int l, int r, int x, vector<int> &a) {
        if(l == r) {
            seg[x] = a[l];
            return;
        }
        build(l, mid, ls, a); build(mid+1, r, rs, a);
        up(x);
    }

    void modify(int p, int v, int l, int r, int x) {
        if(l == r) {
            seg[x] = v;
            return;
        }
        if(p <= mid) modify(p, v, l, mid, ls);
        else modify(p, v, mid+1, r, rs);
        up(x);
    }
    void modify(int p, int v) { modify(p, v, 1, n, 1); }

    int query(int a, int b, int l, int r, int x) {
        if(a <= l and r <= b) return seg[x];
        int res = 0;
        if(a <= mid) res = query(a, b, l, mid, ls);
        if(b > mid) res = op(res, query(a, b, mid+1, r, rs));
        return res;
    }
    void query(int a, int b) { query(a, b, 1, n , 1); }
};
