#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

const int mxN = 2e6 + 5;
struct Node {
    int u = -1, l = -1, r = -1;
    int val;
    Node (int v): val(v) {}
    Node () {}
} nodes[mxN];

int tot = 0;
int st, ed;
int newNode(int v) {
    nodes[++tot] = Node(v);
    return tot;
}

string stk;
void dfs(int idx, int pre) {
    if (idx <= 0) return;
    if (nodes[idx].val == ed) {
        cout << stk << '\n';
        exit(0);
    }

    //cout << "idx = " << idx << '\n';

    stk.push_back('U');
    if (pre != nodes[idx].u) dfs(nodes[idx].u, idx);
    stk.pop_back();

    stk.push_back('L');
    if (pre != nodes[idx].l) dfs(nodes[idx].l, idx);
    stk.pop_back();

    stk.push_back('R');
    if (pre != nodes[idx].r) dfs(nodes[idx].r, idx);
    stk.pop_back();
}

void solve() {
    cin >> st >> ed;

    string tmp;
    int pos_st = 1;

    int root;
    queue<int> q;
    cin >> root;
    q.push(newNode(root));
    while (cin >> tmp) {
        int u = q.front(); 
        int id = 0;
        int val = 0;
        if (tmp[0] != 'n') {
            val = stoi(tmp);
            id = newNode(val);
            q.push(id);
        }
        //cout << "u = " << u << '\n';
        //cout << "val = " << val << '\n';
        if (nodes[u].l == -1) {
            nodes[u].l = id;
            nodes[id].u = u;
        } else if (nodes[u].r == -1) {
            nodes[u].r = id;
            nodes[id].u = u;
            q.pop();
        }
        if (nodes[id].val == st) pos_st = id;
    }

    dfs(pos_st, -1);
}

int main() {
    ios::sync_with_stdio(false), cin.tie(0);
    solve();
}
