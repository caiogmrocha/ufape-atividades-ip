/**
 * @see @link https://judge.beecrowd.com/pt/problems/view/1200
*/

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

typedef struct tree {
    struct tree *left;
    struct tree *right;
    int value;
} Tree;

void insertInBST(Tree **tree, int value) {
    if (*tree == NULL) {
        *tree = (Tree *) malloc(sizeof(Tree));

        (*tree)->left = NULL;
        (*tree)->right = NULL;
        (*tree)->value = value;
    } else {
        if (value < (*tree)->value) {
            insertInBST(&(*tree)->left, value);
        } else {
            insertInBST(&(*tree)->right, value);
        }
    }
}

bool binarySearchInBST(Tree *tree, int value) {
    if (tree == NULL) return false;

    if (value == tree->value) {
        return true;
    } else if (value < tree->value) {
        return binarySearchInBST(tree->left, value);
    } else {
        return binarySearchInBST(tree->right, value);
    }
}

void processPreOrder(Tree *tree, void cb(Tree *tree, char **output), char **output) {
    if (tree != NULL) {
        cb(tree, output);
        processPreOrder(tree->left, cb, output);
        processPreOrder(tree->right, cb, output);
    }
}

void processInOrder(Tree *tree, void cb(Tree *tree, char **output), char **output) {
    if (tree != NULL) {
        processInOrder(tree->left, cb, output);
        cb(tree, output);
        processInOrder(tree->right, cb, output);
    }
}

void processPostOrder(Tree *tree, void cb(Tree *tree, char **output), char **output) {
    if (tree != NULL) {
        processPostOrder(tree->left, cb, output);
        processPostOrder(tree->right, cb, output);
        cb(tree, output);
    }
}

void generatePrintOutput(Tree *tree, char **output) {
    int sizeOfOutput;

    if (*output == NULL) {
        sizeOfOutput = 2;
        *output = (char *) malloc(sizeOfOutput * sizeof(char));
        (*output)[0] = '\0';
    } else {
        sizeOfOutput = strlen(*output) + 3;
        *output = (char *) realloc(*output, sizeOfOutput * sizeof(char));
    }

    char fragment[3] = "";

    sprintf(fragment, "%i ", tree->value);

    *output = strcat(*output, fragment);
}

bool removeFromBST(Tree **tree, int value) {
    if (*tree != NULL) {
        if ((*tree)->value == value) {
            Tree *temp = *tree;
            
            *tree = NULL;

            free(temp);
        } else {
            removeFromBST(&(*tree)->left, value);
            removeFromBST(&(*tree)->right, value);
        }
    }
}

int main() {
    Tree *tree = NULL;
    char input[10];

    while (fgets(input, sizeof(input), stdin)) {
        char *output = NULL;

        if (strcmp(input, "PREFIXA\n") == 0) {
            processPreOrder(tree, generatePrintOutput, &output);
            output[strlen(output) - 1] = '\0';
            printf("%s\n", output);
        } else if (strcmp(input, "INFIXA\n") == 0) {
            processInOrder(tree, generatePrintOutput, &output);
            output[strlen(output) - 1] = '\0';
            printf("%s\n", output);
        } else if (strcmp(input, "POSFIXA\n") == 0) {
            processPostOrder(tree, generatePrintOutput, &output);
            output[strlen(output) - 1] = '\0';
            printf("%s\n", output);
        } else if (input[0] == 'I' && input[1] == ' ') {
            char value[10];

            sprintf(value, "%c", input[2]);

            insertInBST(&tree, atoi(value));
        } else if (input[0] == 'P' && input[1] == ' ') {
            char value[10];

            sprintf(value, "%c", input[2]);

            if (binarySearchInBST(tree, atoi(value))) {
                printf("%c existe\n", input[2]);
            } else {
                printf("%c nao existe\n", input[2]);
            }
        } else if (input[0] == 'R' && input[1] == ' ') {
            char value[10];

            sprintf(value, "%c", input[2]);

            removeFromBST(&tree, atoi(value));
        }

        free(output);
    }

    return 0;
}