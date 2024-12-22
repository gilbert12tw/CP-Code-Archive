// dynamic lazytag segment tree
struct SegmentTree {
    int n, tot, root;
    vector<int> seg, ls, rs;
    vector<pii> tag;
    SegmentTree(int _n): n(_n), tot(0), root(0), seg(_n * 25), ls(_n * 25), rs(_n * 25), tag(_n * 25) {}

#define mid ((l+r)>>1)

    inline int op(const int &a, const int &b) {
        return max(a, b);
    }

    inline void up(int x) {
        seg[x] = op(seg[ls[x]], seg[rs[x]]);
    }

    inline void push_tag(int l, int r, int x, pii v) {
        if (tag[x] == pii(0, 0) || tag[x].first - tag[x].second < v.first - v.second)
            tag[x] = v;
        seg[x] = max(seg[x], tag[x].first + r - tag[x].second + 1);
    }

    inline void down(int l, int r, int x) {
        if (tag[x].first == 0 && tag[x].second == 0) return;
        if (!ls[x]) ls[x] = ++tot;
        if (!rs[x]) rs[x] = ++tot;
        push_tag(l, mid, ls[x], tag[x]);
        push_tag(mid+1, r, rs[x], tag[x]);
        tag[x] = mkp(0, 0);
    }

    void modify(int a, int b, pii v, int l, int r, int &x) {
        if (x == 0) x = ++tot;
        if (l != r) down(l, r, x);
        if(a <= l and r <= b) {
            push_tag(l, r, x, v);
            return;
        }
        if(a <= mid) modify(a, b, v, l, mid, ls[x]);
        if(b > mid) modify(a, b, v, mid+1, r, rs[x]);
        up(x);
    }
    void modify(int a, int b, pii v) { modify(a, b, v, 1, 1e9, root); }

    int query(int a, int b, int l, int r, int &x) {
        if (r < l || b < a) return 0;
        if (!x) return 0;
        if (l != r) down(l, r, x);
        if(a <= l and r <= b) return seg[x];
        int res = 0;
        if(a <= mid) res = query(a, b, l, mid, ls[x]);
        if(b > mid) res = op(res, query(a, b, mid+1, r, rs[x]));
        return res;
    }
    int query(int a, int b) { return query(a, b, 1, 1e9, root); }
};

