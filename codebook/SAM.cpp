struct SAM {
  struct state {
    int len, link, cnt;
    map<char, int> next;
  };

  static const int MAXLEN = 200000; 
  state st[MAXLEN * 2];
  int sz, last;
  vector<vector<int>> tree;

  SAM() {
    st[0].len = 0; st[0].link = -1;
    sz = 1; last = 0;
  }

  void extend(char c) {
    int cur = sz++;
    st[cur].len = st[last].len + 1;
    st[cur].cnt = 1;
    int p = last;
    while (p != -1 && !st[p].next.count(c)) {
      st[p].next[c] = cur;
      p = st[p].link;
    }
    if (p == -1) {
      st[cur].link = 0;
    } else {
      int q = st[p].next[c];
      if (st[p].len + 1 == st[q].len) {
        st[cur].link = q;
      } else {
        int clone = sz++;
        st[clone].len = st[p].len + 1;
        st[clone].next = st[q].next;
        st[clone].link = st[q].link;
        while (p != -1 && st[p].next[c] == q) {
          st[p].next[c] = clone;
          p = st[p].link;
        }
        st[q].link = st[cur].link = clone;
      }
    }
    last = cur;
  }

  void build_tree() {
    tree.resize(sz);
    for (int i = 1; i < sz; i++) {
      tree[st[i].link].eb(i);
    }
  }

  void dfs(int u = 0) {
    for (int v : tree[u]) {
      dfs(v);
      st[u].cnt += st[v].cnt; 
    }
  }
} sam;
