struct MCMF {
    int n;
    vector<int> eu, ev, w, cap;
    vector<vector<int>> g;
    MCMF (int _n): n(_n + 1), g(_n + 1) {}
    inline void add_edge(int x, int y, int ew, int c) {
        g[x].eb(SZ(eu));
        eu.eb(x); ev.eb(y); w.eb(ew); cap.eb(c);
        g[y].eb(SZ(eu));
        ev.eb(x); eu.eb(y); w.eb(-ew); cap.eb(0);
    }
    // longest path by SPFA
    inline int SPFA(int s, int t, int &ans, int &mxflow) {
        vector<int> dis(n, -INF), from(n, 0), in(n, 0), lim(n, 0);
        dis[s] = 0; lim[s] = INF;
        queue<int> q; q.push(s);
        while (!q.empty()) {
            int u = q.front(); q.pop();
            in[u] = 0;
            for (int i : g[u]) {
                int &v = ev[i]; // change this 
                if (cap[i] > 0 && dis[v] < dis[u] + w[i]) {
                    dis[v] = dis[u] + w[i];
                    lim[v] = min(lim[u], cap[i]); 
                    from[v] = i;
                    if (!in[v]) q.push(v);
                    in[v] = 1;
                }
            }
        }
        if (dis[t] <= -INF) return 0;
        int flcnt = lim[t]; // or ans += dis[t]
        ans += dis[t] * flcnt;
        mxflow += flcnt;
        while (t != s) {
            int &e = from[t];	
            cap[e] -= flcnt; cap[e^1] += flcnt; 
            t = eu[e];
        }
        return 1;
    }
    pii run(int s, int t) {
        int ans = 0, fl = 0;
        while (SPFA(s, t, ans, fl));
        return mkp(ans, fl);
    }
};
