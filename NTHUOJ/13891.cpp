#include<iostream>
#include<string>
#include<cassert>
using namespace std;

const int mxN = 2e6 + 5;

int st, ed;
int stk[mxN];

int main() {
    //ios_base::sync_with_stdio(0); cin.tie(0);
    int m;
    cin >> m;
    st = ed = 1000000;
    while (m--) {
        string op;
        cin >> op;
        if (op[0] == 'p') {
            for (int i = st; i < ed; i++) {
                if (i != st) cout << ' ';
                cout << stk[i];;
            }
            cout << '\n';
        } else if (op[0] == 'd') {
            assert(st != ed);
            st++;
        } else if (op[4] == 'n') { // normal customer
            int x; cin >> x;
            stk[ed++] = x;
        } else {
            int p, x;
            cin >> x >> p;
            int ins_pt = st + p - 1;
            int tmp;
            for (int i = ins_pt; i >= st; i--) {
                tmp = stk[i];
                stk[i] = x;
                x = tmp;
            }
            stk[--st] = x;
        }
    }
}
