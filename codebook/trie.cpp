const int mxL = 2e6;
struct Trie {
  int tr[mxL][26], tot = 0;

  void insert(string &s) {
    int cur = 0;
    for (char c : s) {
      int idc = c - 'a';
      int &nxt = tr[cur][idc];
      if (!nxt) nxt = ++tot;
      cur = nxt;
    }
  }
};
