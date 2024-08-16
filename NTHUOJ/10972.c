#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAXEXPR 256
#define NUMSYM 6

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
void printInfix(BTNode *root);

BTNode* makeNode(char c) {
    BTNode *node = (BTNode*)malloc(sizeof(BTNode));
    int i;

    for (i = 0; i < NUMSYM; i++) {
        if (c == sym[i]) {
            node -> data = (TokenSet) i;
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


int main(void){
    sym[0]='A';
    sym[1]='B';
    sym[2]='C';
    sym[3]='D';
    sym[4]='&';
    sym[5]='|';

    scanf("%s", expr);
    pos = strlen(expr) - 1;
    BTNode *root = EXPR();
    printInfix(root);

    return 0;
}

int notLeaf(BTNode *root) {
    if (root -> data == OP_AND || root -> data == OP_OR) return 1;
    return 0;
}

void printInfix(BTNode *root) {

    if (root -> left != NULL) printInfix(root -> left);

    printf("%c", sym[root -> data]);

    if (root -> right != NULL) {
        if (notLeaf(root -> right)) printf("(");
        printInfix(root -> right);
        if (notLeaf(root -> right)) printf(")");
    }
}

void freeTree(BTNode *root) {
    if (root != NULL) {
        freeTree(root -> left); 
        freeTree(root -> right); 
        free(root);
    }
}
