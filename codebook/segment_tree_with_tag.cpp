// lazytag segment tree
struct SegmentTree {
    int n;
    vector<int> seg, tag;
    SegmentTree(int _n): n(_n), seg(_n * 4), tag(_n * 4) {}

#define ls x<<1
#define rs (x<<1)|1
#define mid ((l+r)>>1)

    inline int op(int &a, int &b) {
        return a + b;
    }

    inline void up(int x) {
        seg[x] = op(seg[ls], seg[rs]);
    }

    inline void push_tag(int l, int r, int x, int v) {
        tag[x] += v;	
        seg[x] += v * (r - l + 1);
    }

    inline void down(int l, int r, int x) {
        if(!tag[x]) return;
        push_tag(l, mid, ls, tag[x]);
        push_tag(mid+1, r, rs, tag[x]);
        tag[x] = 0;
    }
    void build(vector<int> &a, int l, int r, int x = 1) {
        if(l == r) {
            seg[x] = a[l];
            return;
        }
        build(a, l, mid, ls);	build(a, mid+1, r, rs);
        up(x);
    } 
    void build(vector<int> &a) { build(a, 0, n, 1); }

    void modify(int a, int b, int v, int l, int r, int x = 1) {
        if(a <= l and r <= b) {
            push_tag(l, r, x, v);
            return;
        }
        if (l != r) down(l, r, x);
        if(a <= mid) modify(a, b, v, l, mid, ls);
        if(b > mid) modify(a, b, v, mid+1, r, rs);
        up(x);
    }
    void modify(int a, int b, int v) { modify(a, b, v, 0, n, 1); }

    int query(int a, int b, int l, int r, int x = 1) {
        if (l != r) down(l, r, x);
        if(a <= l and r <= b) return seg[x];
        int res = 0;
        if(a <= mid) res = query(a, b, l, mid, ls);
        if(b > mid) res = op(res, query(a, b, mid+1, r, rs));
        return res;
    }
    int query(int a, int b) { return query(a, b, 0, n, 1); }
};
