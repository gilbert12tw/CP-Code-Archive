// First include geometry
// in : 1, out : 0, on : -1
// ConvexHull in counterclock wise
int point_in_convex(const vector<PT> &cvx, const PT &p) {
  int l = 0, r = (int)cvx.size() - 1;
  int n = SZ(cvx);
  if (btw(cvx[0], p, cvx[1]) || btw(cvx[0], p, cvx.back())) 
    return -1;
  while (l <= r) {
    int m = (l + r) / 2;
    auto a1 = (cvx[m] - cvx[0]).cross(p - cvx[0]);
    auto a2 = (cvx[(m + 1) % n] - cvx[0]).cross(p - cvx[0]);
    if (a1 >= 0 && a2 <= 0) {
      auto res = (cvx[(m + 1) % n] - cvx[m]).cross(p - cvx[m]);
      return res > 0 ? 1 : (res >= 0 ? -1 : 0);
    }
    if (a1 < 0) r = m - 1;
    else l = m + 1;
  }
  return 0;
}
