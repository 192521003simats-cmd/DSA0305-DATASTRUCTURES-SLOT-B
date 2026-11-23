#include <stdio.h>
#include <stdlib.h>
typedef struct Node {
int key;
struct Node *left, *right;
} Node;
Node *insert(Node *root, int key) {
if (root == NULL) {
Node *n = malloc(sizeof(Node));
n->key = key;
n->left = n->right = NULL;
return n;
}
if (key < root->key)
root->left = insert(root->left, key);
else if (key > root->key)
root->right = insert(root->right, key);
return root;
}
Node *minNode(Node *root) {
while (root && root->left)
root = root->left;
return root;
}
Node *deleteKey(Node *root, int key) {
if (root == NULL)
return NULL;
if (key < root->key)
root->left = deleteKey(root->left, key);
else if (key > root->key)
root->right = deleteKey(root->right, key);
else {
if (!root->left) { Node *t = root->right; free(root); return t; }
if (!root->right){ Node *t = root->left; free(root); return t; }
Node *s = minNode(root->right);
root->key = s->key;
root->right = deleteKey(root->right, s->key);
}
return root;
}
void inorder(Node *root) {
if (!root) return;
inorder(root->left);
printf("%d ", root->key);
inorder(root->right);
}
int height(Node *root) {
if (!root) return -1;
int l = height(root->left), r = height(root->right);
return 1 + (l > r ? l : r);
}
int main(void) {
int a[] = {50, 20, 70, 10, 30, 60, 80, 40, 65};
Node *root = NULL;
for (int i = 0; i < 9; i++) root = insert(root, a[i]);
printf("Inorder: "); inorder(root); printf("\n");
printf("Height: %d\n", height(root));
root = deleteKey(root, 20);
root = deleteKey(root, 50);
printf("After deletions: "); inorder(root); printf("\n");
return 0;
}
