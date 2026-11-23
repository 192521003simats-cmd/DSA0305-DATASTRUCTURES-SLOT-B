#include <stdio.h>
#include <stdlib.h>
typedef enum { RED, BLACK } Color;
typedef struct Node {
int key;
Color color;
struct Node *left, *right, *parent;
} Node;
Node *root = NULL;
void leftRotate(Node *x) {
Node *y = x->right;
x->right = y->left;
if (y->left)
y->left->parent = x;
y->parent = x->parent;
if (x->parent == NULL)
root = y;
else if (x == x->parent->left)
x->parent->left = y;
else
x->parent->right = y;
y->left = x;
x->parent = y;
}
void rightRotate(Node *y) {
Node *x = y->left;
y->left = x->right;
if (x->right)
x->right->parent = y;
x->parent = y->parent;
if (y->parent == NULL)
root = x;
else if (y == y->parent->left)
y->parent->left = x;
else
y->parent->right = x;
x->right = y;
y->parent = x;
}
void fixInsert(Node *z) {
while (z->parent && z->parent->color == RED) {
Node *gp = z->parent->parent;
if (!gp) break;
if (z->parent == gp->left) {
Node *u = gp->right;
if (u && u->color == RED) {
z->parent->color = BLACK; u->color = BLACK;
gp->color = RED; z = gp;
} else {
if (z == z->parent->right) { z = z->parent; leftRotate(z); }
z->parent->color = BLACK; gp->color = RED; rightRotate(gp);
}
} else {
Node *u = gp->left;
if (u && u->color == RED) {
z->parent->color = BLACK; u->color = BLACK;
gp->color = RED; z = gp;
} else {
if (z == z->parent->left) { z = z->parent; rightRotate(z); }
z->parent->color = BLACK; gp->color = RED; leftRotate(gp);
}
}
}
root->color = BLACK;
}
void insert(int key) {
Node *z = malloc(sizeof(Node));
z->key = key; z->color = RED; z->left = z->right = z->parent = NULL;
Node *y = NULL, *x = root;
while (x) { y = x; x = key < x->key ? x->left : x->right; }
z->parent = y;
if (!y) root = z;
else if (key < y->key) y->left = z;
else y->right = z;
fixInsert(z);
}
void inorder(Node *n) {
if (!n) return;
inorder(n->left);
printf("%d(%c) ", n->key, n->color == RED ? 'R' : 'B');
inorder(n->right);
}
int main(void) {
int keys[] = {5, 10, 15, 20, 25, 30};
for (int i = 0; i < 6; i++) insert(keys[i]);
printf("Inorder: "); inorder(root); printf("\n");
Node *mn = root;
while (mn->left) mn = mn->left;
printf("Minimum: %d\n", mn->key);
return 0;
}
