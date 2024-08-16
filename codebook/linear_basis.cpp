struct linear_base {
	int bas[65] = {0}, len = 0;	
	const int mxL = 60;
	void insert(int x) {
		for (int i = mxL; i >= 0; i--) {
			if (get_bit(x, i)) {
				if (bas[i]) x ^= bas[i];
				else {
					bas[i] = x;
					len++;
					break;
				}
			}
		}
	}
	void elimination() {
		for (int i = 0; i < mxL; i++) {
			if (!bas[i]) continue;
			for (int j = i + 1; j <= mxL; j++) {
				if (get_bit(bas[j], i)) bas[j] ^= bas[i];
			}
		}
	}
  int get_max(int res) {
    for (int i = mxL; i >= 0; i--) {
      if (res ^ bas[i] > res) res ^= bas[i];
    }
    return res;
  }
  int get_min(int res) {
    for (int i = mxL; i >= 0; i--) {
      if (res ^ bas[i] < res) res ^= bas[i];
    }
    return res;
  }
};
