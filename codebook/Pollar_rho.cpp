// does not work when n is prime
// return any non-trivial factor
inline llu f(llu x, llu m) { return (mul(x, x, m) + 1) % m; }
inline llu pollard_rho(llu n) {// don't input 1
  if (!(n & 1)) return 2;
  while (true) {
    llu y = 2, x = rand() % (n - 1) + 1, res = 1;
    for (int sz = 2; res == 1; sz *= 2) {
      for (int i = 0; i < sz && res <= 1; i++) {
        x = f(x, n);
        res = gcd(x - y >= 0 ? x - y : y - x, n);
      }
      y = x;
    }
    if (res != 0 && res != n) return res;
  }
}
void fac(llu x, vector<llu> &ans) {
  if (isprime(x)) ans.emplace_back(x);
  else {
    llu p = pollard_rho(x);
    fac(x / p, ans); fac(p, ans);
  }
}
