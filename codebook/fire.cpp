pii rand_vec() {
	double x = rand() * 2 - RAND_MAX;
	double y = rand() * 2 - RAND_MAX;
	return mkp(x, y);
}

void fire() {
	srand(time(NULL));
	pii mid = mkp(5000.0, 5000.0);
	const double delta = 0.995;
	double ans = check(mid), len = 100000.0;	
	while (len > 1e-14) {
		pii v = rand_vec();
		pii nxt = mid + v * len;
		double t = check(nxt), de = t - ans;
		if (de < 0 or (exp(-de / len) * RAND_MAX > rand())) {
			ans = t;
			mid = nxt;
		} 
		len = len * delta;
	}
}
