#include <stdio.h>
#include <stdlib.h>
#define T 2
typedef struct BTree {
int n, leaf;
int keys[2 * T - 1];
struct BTree *child[2 * T];
} BTree;
BTree *createNode(int leaf) {
BTree *node = calloc(1, sizeof(BTree));
node->leaf = leaf;
return node;
}
void splitChild(BTree *parent, int i, BTree *child) {
BTree *newNode = createNode(child->leaf);
newNode->n = T - 1;
for (int j = 0; j < T - 1; j++)
newNode->keys[j] = child->keys[j + T];
if (!child->leaf) {
for (int j = 0; j < T; j++)
newNode->child[j] = child->child[j + T];
}
child->n = T - 1;
for (int j = parent->n; j >= i + 1; j--)
parent->child[j + 1] = parent->child[j];
parent->child[i + 1] = newNode;
for (int j = parent->n - 1; j >= i; j--)
parent->keys[j + 1] = parent->keys[j];
parent->keys[i] = child->keys[T - 1];
parent->n++;
}
void insertNonFull(BTree *node, int key) {
int i = node->n - 1;
if (node->leaf) {
while (i >= 0 && key < node->keys[i]) {
node->keys[i + 1] = node->keys[i]; i--;
}
node->keys[i + 1] = key; node->n++;
} else {
while (i >= 0 && key < node->keys[i]) i--;
i++;
if (node->child[i]->n == 2 * T - 1) {
splitChild(node, i, node->child[i]);
if (key > node->keys[i]) i++;
}
insertNonFull(node->child[i], key);
}
}
BTree *root_g = NULL;
void insert(int key) {
if (!root_g) { root_g = createNode(1); root_g->keys[0] = key; root_g->n = 1; return; }
if (root_g->n == 2 * T - 1) {
BTree *s = createNode(0);
s->child[0] = root_g; splitChild(s, 0, root_g);
int i = key > s->keys[0] ? 1 : 0;
insertNonFull(s->child[i], key);
root_g = s;
} else insertNonFull(root_g, key);
}
int visits_g = 0;
int search(BTree *node, int key) {
visits_g++;
int i = 0;
while (i < node->n && key > node->keys[i]) i++;
if (i < node->n && key == node->keys[i]) return 1;
if (node->leaf) return 0;
return search(node->child[i], key);
}
void inorder(BTree *node) {
if (!node) return;
int i;
for (i = 0; i < node->n; i++) {
if (!node->leaf) inorder(node->child[i]);
printf("%d ", node->keys[i]);
}
if (!node->leaf) inorder(node->child[i]);
}
int main(void) {
int keys[] = {10, 20, 5, 6, 12, 30, 7, 17};
for (int i = 0; i < 8; i++) insert(keys[i]);
printf("Sorted keys: "); inorder(root_g); printf("\n");
visits_g = 0;
printf("Search 17: %s\n", search(root_g, 17) ? "Found" : "Not Found");
printf("Node visits: %d\n", visits_g);
return 0;
}
