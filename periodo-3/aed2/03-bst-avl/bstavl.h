#ifndef BSTAVL_H
#define BSTAVL_H

typedef struct bst {
    int value;
    struct bst *left, *right;
} bst;

bst *bstFactory(int value);
void bstInsert(bst **dest, bst *source);
void bstPreOrder(bst *tree, void cb(bst *node));
void bstInOrder(bst *tree, void cb(bst *node));
void bstPostOrder(bst *tree, void cb(bst *node));
void bstRemove(bst **tree, int value);
bst *bstRotateLeft(bst **tree, int value);
bst *bstRotateRight(bst **tree, int value);
// void bstRotateLeftRight(bst **tree);
// void bstRotateRightLeft(bst **tree);

#endif