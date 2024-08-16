#ifndef FUNCTION_H
#define FUNCTION_H

#define MAXEXPR 256
#define NUMSYM 6

#include <stdio.h>
#include <stdlib.h>

char expr[MAXEXPR];  // string to store the input expression.
int pos;             // current position of parsing, from end to start

typedef enum {ID_A, ID_B, ID_C, ID_D, OP_AND, OP_OR} TokenSet;
char sym[NUMSYM];

typedef struct _Node {
    TokenSet data;
    struct _Node *left, *right;
} BTNode;

BTNode* EXPR();
BTNode* FACTOR();
BTNode* makeNode(char c);
void freeTree(BTNode *root);
void printPrefix(BTNode *root);

BTNode* makeNode(char c) {
    BTNode *node = (BTNode*)malloc(sizeof(BTNode));
    int i;

    for (i = 0; i < NUMSYM; i++) {
        if (c == sym[i]) {
            node->data = i;
            break;
        }
    }

    node -> left = NULL;
    node -> right = NULL;
    return node;
}

// EXPR = FACTOR | EXPR OP FACTOR
BTNode* EXPR() {
    BTNode *node = NULL, *right = NULL;
    if (pos >= 0) {
        right = FACTOR();
        if (pos > 0) {
            char cur = expr[pos];
            if (cur == '&' || cur == '|') {
                node = makeNode(cur);
                node -> right = right;
                pos--;
                node -> left = EXPR();
            } else if (cur == '('){
                // '(' case
                node = right;
            } else {
                //printf("Error EXPR");
            }
        } else {
            node = right;
        }
    }
    return node;
}

BTNode* FACTOR() {
    BTNode *node = NULL;
    if (pos >= 0) {
        char cur = expr[pos--];
        if (cur == ')') { // FACTOR = (EXPR)
            node = EXPR();
            if (expr[pos--] != '(') {
                //printf("Error!\n");
                freeTree(node);
            }
        } else { // FACTOR = ID
           node = makeNode(cur);
        }
    }
    return node;
}
#endif

