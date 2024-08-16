#include<bits/stdc++.h>
#include <bits/extc++.h>
using namespace std;
using namespace __gnu_pbds;

// order_of_key, find_by_order
using BST = tree<int, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update>;

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    int n, q; cin >> n >> q;
    map<int, BST> st;
    map<int, vector<int>> job;
    for (int i = 1; i <= n; i++) {
        int t; cin >> t;
        st[t].insert(i);
    }
    
    vector<int> cute(n + 1);
    int gg = 0;
    while (q--) {
        string act, type;
        int id, k, x;
        cin >> act >> id;
        if (act == "Quit") {
            for (int j : job[id])
                cute[j] = 0;
        } else {
            cin >> k >> type;
            vector<int> tmp;
            map<int, int> cnt;
            gg = 0;
            for (int i = 0; i < k; i++) {
                cin >> x; cnt[x]++;
                if ((int)st[x].size() < cnt[x]) gg = 1;
                tmp.emplace_back(x);
            }
            if (gg) tmp.clear();
            for (int i : tmp) {
                int get_job = -1;
                assert(type == "MIN" || type == "MAX");
                if (type == "MAX") {
                    get_job = *st[i].rbegin();
                } else if (type == "MIN") {
                    get_job = *st[i].begin();
                } else {
                    get_job = *st[i].find_by_order((st[i].size() + 1) / 2 - 1);
                }
                st[i].erase(get_job);
                job[id].emplace_back(get_job);
                cute[get_job] = id;
            }
        }
        if (gg) break;
    }
    for (int i = 1; i <= n; i++)
        cout << cute[i] << ' ';
    cout << '\n';
}
