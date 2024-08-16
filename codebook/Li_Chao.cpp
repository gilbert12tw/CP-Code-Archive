struct LC_tree {
    struct Line {
        pii line;
        int ls = 0, rs = 0;
    } seg[mxN * 15];
    inline int cal(pii l, int x) {
        return l.first * x + l.second;
    }
    int tot = 0;

    void insert(pii t, int &id, int l, int r) {
        if (id == 0) id = ++tot;
        int mid = (l+r) >> 1;
        if (cal(t, mid) > cal(seg[id].line, mid)) swap(t, seg[id].line);
        if (l == r)  return;
        if (cal(t, l) > cal(seg[id].line, l)) insert(t, seg[id].ls, l, mid);
        if (cal(t, r) > cal(seg[id].line, r)) insert(t, seg[id].rs, mid+1, r);
    }

    int query(int p, int id, int l, int r) {
        if (id == 0) return -INF;
        if (l == r) return cal(seg[id].line, p);
        int mid = (l+r)>>1;
        if (p <= mid) return max(query(p, seg[id].ls, l, mid), cal(seg[id].line, p));
        else return max(query(p, seg[id].rs, mid+1, r), cal(seg[id].line, p));
    }
} LCT;
