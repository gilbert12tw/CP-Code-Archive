#include <iostream>
#include <stdio.h>
#include <string>
#include <cassert>

#define de(x) cout << #x << " = " << x << endl

using namespace std;

int max(int a, int b) {
    return (a > b ? a : b);
}
int max(int a, int b, int c) {
    return max(a, max(b, c));
}
void swap(int &a, int &b) {
    int t = a; a = b; b = t;
}

struct Node {
    int id, hp, lv;
    Node *nxt, *prv;

    Node (): lv(1) {}
    Node (int _id, int _hp): id(_id), hp(_hp), lv(1) {}

    void insert(Node *u) {
        u->nxt = nxt;
        u->prv = this;
        nxt->prv = u;
        nxt = u;
    }

    void insert_prev(Node *u) {
        prv->insert(u);
    }

    void remove() {
        prv->nxt = nxt;
        nxt->prv = prv;
    }
};

Node* stk[10005];
int tp;
int cnt[105];

struct List {
    Node* cur = nullptr;
    int sz = 0;
    void insert(Node *u) {
        sz++;
        if (sz == 1) {
            cur = u;
            cur->nxt = cur->prv = u;
            return;
        }
        cur->insert_prev(u);
    }
    void del(Node *u) {
        sz--;
        if (u == cur) 
            cur = cur->nxt;
        u->remove();
    }
    void shuffle(char cc, int k) {
        k %= sz;
        Node *u = cur;
        while (k--) {
            if (cc == 'a') u = u->prv;
            else u = u->nxt;
        }
        swap(cur->id, u->id);
        swap(cur->hp, u->hp);
        swap(cur->lv, u->lv);
        cur = u;
    }
    void reverse(int k) {
        if (k > sz) k = sz;
        if (k == 1) return;
        Node *u = cur;
        while (1) {
            int i = 0;
            tp = 0;
            Node *p = u;

            do {
                stk[tp++] = u;
                u = u->nxt;
                u->prv->remove();
                i++;
            } while (u != cur && i < k);
            
            if (p == cur) {
                cur = stk[tp - 1];
            }

            while (tp > 0) {
                u->insert_prev(stk[--tp]);
            }

            if (u == cur) break;
        }
    }
    void check(int k) {
        for (int i = 0; i <= 100; i++) cnt[i] = 0;
        if (k > sz) k = sz;
        Node *u = cur;
        for (int i = 0; i < k; i++) {
            cnt[u->id]++;
            u = u->nxt;
        }
        u = cur;
        for (int i = 0; i < k; i++) {
            if (cnt[u->id] > 1) {
                u = u->nxt;
                del(u->prv);
                continue;
            }
            u = u->nxt;
        }
    }
    void print() { 
        int n = sz;
        if (n == 0) {
            cout << "no Poke Poke ;-;\n";
            return;
        }
        Node *u = cur;
        while (n--) {
            cout << "ID: " << u->id << " HP: " << u->hp << " LVL: " << u->lv << '\n';
            u = u->nxt;
        }
    }
} current;

int main() {
    int q; cin >> q;
    while (q--) {
        string op, state;
        int a, b, c;
        char cc;
        Node *nw;

        cin >> op;
        switch (op[0]) {
            case 'I':
                cin >> a >> b >> c >> state;
                // id, atk, hp
                nw = new Node(a, c);
                current.insert(nw);
                if (current.sz == 1) break;
                if (state == "Attack") {
                    int flag = (current.sz == 2);
                    if (nw->nxt->hp <= b) {
                        current.cur = nw;
                        current.del(nw->nxt);
                    } else {
                        nw->nxt->hp -= b;
                    }
                    if (flag) break;
                    if (nw->prv->hp <= b) {
                        current.del(nw->prv);
                    } else {
                        nw->prv->hp -= b;
                    }
                } else if (state == "Evolve") {
                    if (current.sz < 3) break;
                    int mxlv = max(nw->nxt->lv, nw->prv->lv);
                    int mxhp = max(nw->nxt->hp, nw->prv->hp, c);
                    if (mxlv == 3 || a != nw->nxt->id || a != nw->prv->id) 
                        break;
                    nw->lv = mxlv + 1;
                    nw->hp = mxhp;
                    current.cur = nw;
                    current.del(nw->prv);
                    current.del(nw->nxt);
                }
                break;
            case 'D':
                current.del(current.cur);
                break;
            case 'S':
                cin >> cc >> a;
                current.shuffle(cc, a);
                break;
            case 'R':
                cin >> a;
                current.reverse(a);
                break;
            case 'C':
                cin >> a;
                current.check(a);
                break;
            default:
                break;
        }

        continue;
        cout << "test\n";
        current.print();
        cout << "\n";
    }
    current.print();
    return 0;
}
