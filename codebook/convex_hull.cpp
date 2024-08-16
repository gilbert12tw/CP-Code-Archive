bool cmp(const PT &a, const PT &b) {
	if(a.x == b.x) return a.y < b.y;
	return a.x < b.x;
}

vector<PT> build(vector<PT> p) {
	vector<PT> up, dn;	
	sort(ALL(p), cmp);
	for(int i = 0; i < n; i++) {
		while(SZ(up) > 1 && 
        (up[SZ(up) - 1] - up[SZ(up) - 2]).cross(p[i] - up[SZ(up) - 2]) > 0)
			up.pop_back();
		while(SZ(dn) > 1 && 
        (dn[SZ(dn) - 1] - dn[SZ(dn) - 2]).cross(p[i] - dn[SZ(dn) - 2]) < 0)
			dn.pop_back();
		dn.pb(p[i]);
		up.pb(p[i]);
	}
	reverse(ALL(dn));
	for (int i = 1; i + 1 < SZ(dn); i++) up.eb(dn[i]);
	return up;
}
