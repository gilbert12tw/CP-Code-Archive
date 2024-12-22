#include<bits/stdc++.h>
#pragma GCC optimize("Ofast, unroll-loops")
using namespace std;
#define mp make_pair
#define SZ(x) ((int)x.size())
#define eb emplace_back
typedef long long ll;

const int mxL = 2e6 + 1;
const int mxC = 94;


#define tp pair<pair<int, int>, int>

inline int ch(char c) {
    return (c - 33);
};

struct Trie {
    int tr[96][mxL];
    int tot = 0, ord = 0;
    vector<int> idx[mxL];
    set<tp> st[mxL];
    void init() {
        tot = ord = 0;
    }
    void ins_1(const string &s, int id) {
        int cur = 0;
        for (char c : s) {
            int &nxt = tr[ch(c)][cur];
            if (nxt == 0) nxt = ++tot;
            cur = nxt;
        }
        idx[cur].eb(id);
    }

    void insert(const string &s, tp t) {
        int cur = 0;
        st[0].insert(t);
        for (char c : s) {
            int &nxt = tr[ch(c)][cur];
            assert(nxt != 0);
            cur = nxt;
            st[cur].insert(t);
        }
    }

    void del(const string &s, tp t) {
        int cur = 0;
        st[0].erase(t);
        for (char c : s) {
            int &nxt = tr[ch(c)][cur];
            assert(nxt != 0);
            cur = nxt;
            st[cur].erase(t);
        }
    }

    void dfs(int u, vector<int> &lex) {
        if (!idx[u].empty()) ord++;
        for (int id : idx[u]) {
            lex[id] = ord;
        }
        for (int i = 0; i < mxC; i++) {
            if (tr[i][u]) dfs(tr[i][u], lex);
        }
    }
};

struct Query {
    int type, x;
    string s;
};

int main () {
    ios_base::sync_with_stdio(0); cin.tie(0);
    int q; cin >> q;    
    
    vector<Query> qry;
    vector<int> lex(q + 1, -1);
    vector<string> pat(q + 1);
    Trie trie;
    for (int i = 0; i < q; i++) {
        string t, p; int x;
        cin >> t;
        if (t == "add") {
            cin >> x >> p;
            qry.eb(Query{0, x, p});
            trie.ins_1(p, x);
            pat[x] = p;
        } else if (t == "delete") {
            cin >> x;
            qry.eb(Query{1, x, pat[x]});
        } else if (t == "append") {
            cin >> p;
            qry.eb(Query{2, 0, p});
        } else if (t == "backspace") {
            cin >> x;
            qry.eb(Query{3, x, ""});
        }
    }
    trie.dfs(0, lex);
    
    map<int, tp> mmp;
    vector<int> traj;
    traj.eb(0);

    for (int i = 0; i < q; i++) {
        int type = qry[i].type;
        int id = qry[i].x;
        string s = qry[i].s;

        if (type == 0) {
            tp tmp = mp(mp(-SZ(s), lex[id]), id);
            mmp[id] = tmp;
            trie.insert(s, tmp);
        } else if (type == 1) {
            tp tmp = mmp[id];
            trie.del(s, tmp);
        } else if (type == 2) {
            int cur = traj.back();
            int ok = 1;
            for (char c : s) {
                int &nxt = trie.tr[ch(c)][cur];
                if (nxt == 0) ok = 0;
                cur = nxt;
                if (ok) traj.eb(cur);
                else traj.eb(-1);
            }
        } else {
            int rn = id;
            while (rn-- && SZ(traj) > 1) traj.pop_back();
        }

        if (traj.back() == -1) {
            cout << -1 << '\n';
            continue;
        } 
        int tid = traj.back();
        /*
        cout << "tid = " << tid << '\n';
        cout << "sz = " << SZ(traj) << '\n';
        */
        if (trie.st[tid].empty()) cout << -1 << '\n';
        else cout << trie.st[tid].begin()->second << '\n';
    }
}

/*
6
add 1 pattern1_alice
add 2 pattern2_bob
add 3 pattern3_charlie
append pattern
append 2_bobabc
backspace 3
*/

/*
6
append pattern
add 1 pattern1_alice____
add 2 pattern2_bob______
add 3 pattern3_charlie__
delete 1
delete 2
*/
