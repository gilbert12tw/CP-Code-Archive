

for (int v : adj[u]) {
    if (dis[v] == -1) { // dis 初始化為 -1
        dis[v] = dis[u] + 1;
        q.push(v);
    }
}



