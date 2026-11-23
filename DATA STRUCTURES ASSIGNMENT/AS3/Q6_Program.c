#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct Trie {
struct Trie *child[26];
int words;
int end;
} Trie;
Trie *createNode(void) {
return calloc(1, sizeof(Trie));
}
void insert(Trie *t, const char *w) {
for (int i = 0; w[i]; i++) {
int idx = w[i] - 'a';
if (!t->child[idx])
t->child[idx] = createNode();
t = t->child[idx];
t->words++;
}
t->end = 1;
}
int countPrefix(const Trie *t, const char *p) {
for (int i = 0; p[i]; i++) {
int idx = p[i] - 'a';
if (!t->child[idx]) return 0;
t = t->child[idx];
}
return t->words;
}
void collect(Trie *t, char *buf, int depth) {
if (t->end) { buf[depth] = '\0'; printf("%s ", buf); }
for (int i = 0; i < 26; i++) {
if (t->child[i]) {
buf[depth] = 'a' + i;
collect(t->child[i], buf, depth + 1);
}
}
}
int search(Trie *t, const char *w) {
for (int i = 0; w[i]; i++) {
int idx = w[i] - 'a';
if (!t->child[idx]) return 0;
t = t->child[idx];
}
return t->end;
}
void rangeSearch(const char **words, int n, const char *lo, const char *hi) {
for (int i = 0; i < n; i++)
if (strcmp(words[i], lo) >= 0 && strcmp(words[i], hi) <= 0)
printf("%s ", words[i]);
printf("\n");
}
void freeTrie(Trie *t) {
if (!t) return;
for (int i = 0; i < 26; i++) freeTrie(t->child[i]);
free(t);
}
void destroy(Trie *root) {
if (root) {
for (int i = 0; i < 26; i++)
destroy(root->child[i]);
free(root);
}
}
int main(void) {
const char *names[] = {
"anand", "anitha", "anu",
"arun", "bala", "anusuya"
};
Trie *root = createNode();
for (int i = 0; i < 6; i++) insert(root, names[i]);
const char *prefixes[] = {"a", "an", "anu", "b", "z"};
for (int i = 0; i < 5; i++)
printf("%s : %d\n", prefixes[i], countPrefix(root, prefixes[i]));
destroy(root);
/* Extended: autocomplete and range search */
const char *words[] = {"apple", "apply", "apt", "band", "banana", "cat"};
int n = 6;
Trie *root2 = createNode();
for (int i = 0; i < n; i++) insert(root2, words[i]);
printf("Exact search for band: %s\n",
search(root2, "band") ? "Found" : "Not Found");
printf("Autocomplete for ap: ");
Trie *current = root2;
char prefix[] = "ap";
int valid = 1;
for (int i = 0; prefix[i]; i++) {
int index = prefix[i] - 'a';
if (index < 0 || index >= 26 || current->child[index] == NULL) {
valid = 0; break;
}
current = current->child[index];
}
if (valid) {
char buffer[128] = "ap";
collect(current, buffer, 2);
printf("\n");
} else printf("No matches\n");
printf("Range banana to cat: ");
rangeSearch(words, n, "banana", "cat");
freeTrie(root2);
return 0;
}
