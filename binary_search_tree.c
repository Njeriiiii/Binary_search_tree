#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node* left;
    struct Node* right;
} Node;

Node* createNode(int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

Node* bst_construct(int inOrder[], int postOrder[], int inStart, int inEnd, int* postIndex, int n) {
    if (inStart > inEnd) {
        return NULL;
    }

    int rootData = postOrder[(*postIndex)--];
    Node* root = createNode(rootData);

    int rootIndex = -1;
    for (int i = inStart; i <= inEnd; i++) {
        if (inOrder[i] == rootData) {
            rootIndex = i;
            break;
        }
    }

    root->right = bst_construct(inOrder, postOrder, rootIndex + 1, inEnd, postIndex, n);
    root->left = bst_construct(inOrder, postOrder, inStart, rootIndex - 1, postIndex, n);

    return root;
}

void dfs_traversal(Node* root) {
    if (root == NULL) {
        return;
    }

    printf("%d ", root->data);
    dfs_traversal(root->left);
    dfs_traversal(root->right);
}

int main() {
    int inOrder[] = {5, 10, 15, 20, 25, 30, 45};
    int postOrder[] = {5, 15, 10, 25, 45, 30, 20};
    int n = sizeof(inOrder) / sizeof(inOrder[0]);
    int postIndex = n - 1;

    Node* root = bst_construct(inOrder, postOrder, 0, n - 1, &postIndex, n);

    printf("DFS Traversal: ");
    dfs_traversal(root);
    printf("\n");

    return 0;
}
