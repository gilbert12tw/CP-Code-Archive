int nxt[mxN], f[mxN];

void kmp(string a, string b) {
	int n = sz(a), m = sz(b);
	for(int i = 2, j = 0; i <= m; i++) {
		while(j and b[j + 1] != b[i]) j = nxt[j];
		if(b[j + 1] == b[i]) j++;
		nxt[i] = j;
	}
	for(int i = 1, j = 0; i <= n; i++) {
		while(j and (j == m or b[j + 1] != a[i])) j = nxt[j];
		if(b[j + 1] == a[i]) j++;
		f[i] = j;
	}
}
