int np[mxN];
vector<int> prime;

void sieve(int n) {
	for(int i = 2; i <= n; i++) {
		if(np[i] == 0) np[i] = i, prime.eb(i);
		for(int j : prime) {
			if(i * j > n) break;
			np[i * j] = j;
			if(np[i] == j) break;
		}
	}
}
