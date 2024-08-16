struct auto_AC_machine {
	static const int mxN = 5e5 + 5;
	int trie[mxN][26], ed[mxN], fail[mxN], dp[mxN], tot; 
	inline int insert(string &s) {
		int u = 0;
		for(auto i : s) {
			if(!trie[u][i - 'a']) trie[u][i - 'a'] = ++tot;
			u = trie[u][i - 'a'];
		}
		ed[u]++;
		return u;
	}
	 
	int topo[mxN], tp;
	inline void build() {
		queue<int> q; q.push(0);
		tp = 0;
		while(!q.empty()) {
			int u = q.front(); q.pop();
			topo[tp++] = u;
			for(int i = 0; i < 26; i++) {
				int &to = trie[u][i];
				if(to) {
					fail[to] = (u == 0 ? 0 : trie[fail[u]][i]);	
					q.push(to);
				} else to = trie[fail[u]][i];
			}
		}
	}
	
	inline void DP() {
		for (int i = tp - 1; i >= 0; i--) {
			int u = topo[i];
			// do something
		}
	}
} AC;
