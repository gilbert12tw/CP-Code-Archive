// 0-index
struct Hash {
  static const int p = 13331, q = 1e9 + 7;
  vector<int> hsh, pp;

  Hash(string s) {
    int n = s.size();
    hsh.resize(n);
    pp.resize(n);
    hsh[0] = s[0]; pp[0] = 1;
    for (int i = 1; i < n; i++) {
      hsh[i] = (hsh[i-1] * p % q + s[i]) % q;
      pp[i] = pp[i-1] * p % q;
    }
  }

  int get(int l, int r) {
    if (l == 0) return hsh[r];
    int tmp = (hsh[r] - (hsh[l - 1] * pp[r - l + 1] % q)) % q;
    if (tmp < 0) tmp += q;
    return tmp;
  }
};

