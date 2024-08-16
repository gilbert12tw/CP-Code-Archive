// Source: https://usaco.guide/general/io

#include <bits/stdc++.h>
using namespace std;

int main() {
	int n; cin >> n;
	vector<int> x(n);
	for (int i = 0; i < n; i++) {
		cin >> x[i];
	}
	set<int> st;
	for (int i = 0; i < n; i++) {
		if (st.empty() || *st.rbegin() < x[i]) { // size + 1
			st.insert(x[i]);
		} else { // replace
			if (st.find(x[i]) != st.end()) {
				// Bug 
				// 如果 set 中已經有一樣的數字就不用作交換了
				continue;
			}
			auto it = st.upper_bound(x[i]);
			st.erase(it);
			st.insert(x[i]);
		}
	}
	cout << st.size() << '\n';
}

