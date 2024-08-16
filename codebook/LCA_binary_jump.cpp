// LCA
const int mxN = 200005;
const int lgN = 20;
int timer;
int in[mxN], out[mxN], dep[mxN], fa[lgN][mxN];
void dfs(int u = 1, int p = 1) {
    in[u] = ++timer;
    fa[0][u] = p;
    for (int i = 1; i < lgN; i++) 
        fa[i][u] = fa[i-1][fa[i-1][u]];
    for (int v : tree[u]) {
        if (v != p) {
            dep[v] = dep[u] + 1;
            dfs(v, u);
        }
    }
    out[u] = timer;
}

bool ancestor(int u, int v){
    return in[u] <= in[v] && out[u] >= out[v];
}
 
int lca(int u, int v){
    if(ancestor(u, v))  return u;
    if(ancestor(v, u))  return v;
    for(int i = lgN - 1; i >= 0; i--)
        if(!ancestor(fa[i][u], v))
            u = fa[i][u];
    return fa[0][u];
}
 
inline int dis(int u, int v){
    test(u, v, lca(u, v));
    test(dep[u], dep[v], dep[lca(u, v)]);
    return dep[u] + dep[v] - 2 * dep[lca(u, v)];
}
