#include<iostream>
#include<algorithm>
#include<vector>
#include<list>
using namespace std;

#define x first
#define y second
#define pii pair<int, int>
#define pb push_back
#define all(x) x.begin(), x.end()
#define de(x) cout << #x << " = " << x << endl

list<pair<int, int>> lst[100];

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    int n, q; cin >> n >> q;
    while (q--) {
        string op;
        cin >> op;
        int a, b, c;
        if (op == "Insert") {
            cin >> a >> b >> c;
            lst[a].push_back(make_pair(b, c)); // ID, Level
        } else if (op == "Remove") {
            cin >> a >> b;
            auto it = lst[a].begin();
            while (it != lst[a].end()) {
                if (it->first == b) {
                    it = lst[a].erase(it);
                    continue;
                }
                it = next(it);
            }
        } else if (op == "Rotate") {
            cin >> a >> b;
            b %= (lst[a].size());
            while (b--) {
                auto tmp = lst[a].back();
                lst[a].pop_back();
                lst[a].push_front(tmp);
            }
        } else if (op == "Reorder") {
            cin >> a;
            vector<pair<int, int>> tmp[2];
            int cnt = 0;
            for (auto p : lst[a]) {
                tmp[(cnt++) % 2].push_back(p);
            }
            lst[a].clear();
            for (int i = 0; i <= 1; i++) {
                for (auto p : tmp[i])
                    lst[a].push_back(p);
            }
        } else if (op == "Reverse") {
            cin >> a >> b >> c;
            vector<pair<int, int>> tmp;
            int cnt = 0;
            for (auto p : lst[a]) {
                if (cnt >= b && cnt <= c) {
                    tmp.push_back(p); 
                }
                cnt++;
            }
            auto it = lst[a].begin();
            cnt = 0;
            while (it != lst[a].end()) {
                if (cnt >= b && cnt <= c)  {
                    it = lst[a].erase(it);
                } else {
                    it = next(it);
                }
                cnt++;
            }
            it = lst[a].begin();
            while (b > 0) {
                it = next(it);
                b--;
            }
            reverse(tmp.begin(), tmp.end());
            for (auto p : tmp) lst[a].insert(it, p);
        } else if (op[0] == 'M') {
            cin >> a >> b;
            vector<pair<int, int>> va, vb;
            int ma = lst[a].size(), mb = lst[b].size();
            for (auto p : lst[a]) va.push_back(p);
            for (auto p : lst[b]) vb.push_back(p);
            int i = 0, j = 0;
            lst[b].clear();
            vector<pair<int, int>> tmp;
            while (i != ma && j != mb) {
                if (va[i] == vb[j]) {
                    tmp.push_back(va[i++]);
                } else if (va[i].second < vb[j].second) {
                    tmp.push_back(va[i++]);
                } else if (va[i].second > vb[j].second) {
                    tmp.push_back(vb[j++]);
                } else {
                    if (va[i].first < vb[j].first) 
                        tmp.push_back(va[i++]);
                    else 
                        tmp.push_back(vb[j++]);
                }
            }
            while (i == ma && j < mb) tmp.push_back(vb[j++]);
            while (j == mb && i < ma) tmp.push_back(va[i++]);
            lst[a].clear();
            for (auto p : tmp) lst[a].push_back(p);
        }
    }
    for (int i = 0; i < n; i++) {
        cout << "List " << i << '\n';
        if (lst[i].empty()) {
            cout << "Empty\n";
            continue;
        }
        for (auto [id, lv] : lst[i]) {
            cout << "ID: " << id << " Level: " << lv << '\n';
        }
    }
}

