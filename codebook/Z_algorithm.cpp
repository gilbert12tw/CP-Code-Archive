int z[mxN];
void cal_z(string s) {
	z[0] = sz(s);
	int n = z[0], l = 0, r = 0;
	for(int i = 1; i < n; i++) {
		z[i] = r > i ? min(r - i + 1, z[i - l]) : 0;
		while(s[i + z[i]] == s[z[i]]) z[i]++;
		if(z[i] > r) l = i, r = i + z[i] - 1;
	}
}

