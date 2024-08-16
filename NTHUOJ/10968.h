#ifndef FUNCTION_H
#define FUNCTION_H

#include <stdio.h>
#include <stdlib.h>


typedef struct treeNode {
    char data;
    struct treeNode *left;
    struct treeNode *right;
} Node;

void constructTree(Node** head);
void printInfix(Node *root);
void freeTree(Node *root);

int notLeaf(Node *root) {
    if (root -> data == '&' || root -> data == '|') return 1;
    return 0;
}

void printInfix(Node *root) {

    if (root -> left != NULL) printInfix(root -> left);

    printf("%c", root -> data);

    if (root -> right != NULL) {
        if (notLeaf(root -> right)) printf("(");
        printInfix(root -> right);
        if (notLeaf(root -> right)) printf(")");
    }
}

#endif
