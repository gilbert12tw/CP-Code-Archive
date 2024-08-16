#include <stdlib.h>
#include <stdio.h>

typedef struct _Node {
    int data;
    struct _Node *next;
} Node;

void deleteNode(Node ** nd, int data);
Node* createList();

#define new_node (Node*)malloc(sizeof(Node))
Node * createList() {
    Node *head = NULL, *prv = NULL;
    while (1) {
        int val;
        scanf("%d", &val);
        if (val == -1) break;
        Node *cur = new_node;
        cur->data = val;
        if (prv != NULL) prv->next = cur;
        if (head == NULL) head = cur;
        prv = cur;
    }
    return head;
}

void deleteNode(Node **nd, int data) {
    Node *tmp = NULL;
    if (data == 1) {
        tmp = *nd;
        *nd = tmp->next;
        free(tmp);
    } else {
        Node *cur = *nd;
        for (int i = 1; i < data; i++) { 
            tmp = cur; 
            if (cur != NULL) cur = cur->next;
        }
        if (tmp != NULL && cur != NULL) tmp->next = cur->next;
        if (cur != NULL) free(cur);
    }
}
