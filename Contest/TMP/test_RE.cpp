#include <bits/stdc++.h>

using namespace std;

struct node {
    int val;
    node* pre, *next;
    node(int val, node* pre, node* next) : val(val), pre(pre), next(next) {}
};

    node* heads[2000001];
    node* nodes[2000001];

int main() {
    int n, m;
    scanf("%d %d", &n, &m);
    for(int i=1;i<=n;i++) {
        heads[i] = new node(-1, nullptr, nullptr);
        heads[i]->next = new node(i, heads[i], heads[i]);
        heads[i]->pre = heads[i]->next;
        nodes[i] = heads[i]->next;
    }
    int cmd, a, b;
    for(int i=0;i<m;i++) {
        scanf("%d %d %d", &cmd, &a, &b);
        if(cmd == 0) {
            node* n1 = nodes[a];
            node* n2 = nodes[b];
            if (n1->next != nullptr) n1->next->pre = n1->pre;
            n1->pre->next = n1->next;
            n1->pre = n2;
            if (n1->next != nullptr) n1->next = n2->next;
            if (n2->next != nullptr) n2->next->pre = n1;
            if (n2->next != nullptr) n2->next = n1;
        } else {
            node* ha = heads[a]->next;
            node* ta = heads[a]->pre;
            node* tb = heads[b]->pre;
            if(ha->val != -1) {
                ha->pre = tb;
                ta->next = heads[b];
                tb->next = ha;
                heads[b]->pre = ta;
                heads[a]->pre = heads[a];
                heads[a]->next = heads[a];
            }
        }
    }

    for(int i=1;i<=n;i++) {
        node* tmp = heads[i]->next;
        printf("#%d:", i);
        while(tmp->val != -1) {
            printf(" %d", tmp->val);
            tmp = tmp->next;
        }
        printf("\n");
    }
    return 0;
}
