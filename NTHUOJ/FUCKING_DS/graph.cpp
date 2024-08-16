const int mxN = 1000, mxE = 1000;

struct Graph {
    int h[mxN];
    int cnt;

    Graph() {
        memset(h, -1, sizeof h);
        cnt = 0;
    }

    struct Edge{
        int to, next, cost;
    } rng[MAX_E];

    void add(int u, int v, int cost){
        rng[cnt].to = v;
        rng[cnt].next = h[u];
        rng[cnt].cost = cost;
        h[u] = cnt++;
    }
};
