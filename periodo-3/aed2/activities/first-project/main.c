#include <stdio.h>

#include "modules/avl.h"

int main() {
    printf("Hello World!\n");

    avl *tree = NULL;

    avlInsert(&tree, 20);
    avlInsert(&tree, 30);
    avlInsert(&tree, 25);
    avlInsert(&tree, 35);
    avlInsert(&tree, 32);

    // avlRemove(&tree, 30);
    avlRemove(&tree, 30);

    printf("Value: %i\n", tree->value);

    return 0;
}