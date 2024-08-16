int phi[mxN], np[mxN];
vector<int> prime;

void build_phi(int n) {
	phi[1] = 1;
	for(int i = 2; i <= n; i++) {
		if(np[i] == 0) {
			prime.pb(i);
			np[i] = i;
			phi[i] = i - 1;
		}
		for(int j : prime) {
			if(j * i > n) break;
			np[i * j] = j;
			if(np[i] == j) {
				phi[i * j] = phi[i] * j;
				break;
			} else {
				phi[i * j] = phi[i] * (j - 1);
			}
		}
	}
}
