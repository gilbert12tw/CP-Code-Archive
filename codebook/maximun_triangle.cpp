double roate_ruler(vector<PT> cvx) {
	int n = SZ(cvx), ans = 0;
	for (int i = 0; i < n; i++) {
		int j = (i + 1) % n;
		int k = (j + 1) % n;
		while (j != k && k != i) {
			ans = max(ans, area(cvx[i], cvx[j], cvx[k]));
			while (cross(cvx[i] - cvx[j], cvx[(k + 1) % n] - cvx[k]) < 0) {
				k = (k + 1) % n;
				ans = max(ans, area(cvx[i], cvx[j], cvx[k]));
			}
			j = (j + 1) % n;
		}
	}

	double res = ans / 2.0;
	return res;
}
