/* Q7 – Dictionary and Spell-Checker using Trie + Sorted Array
* Implements: exact look-up, autocomplete, alphabetical range listing.
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_WORDS 1000
#define MAX_LEN 64
/* ── Trie for exact look-up and autocomplete ── */
typedef struct Trie {
struct Trie *child[26];
int is_end;
} Trie;
Trie *trieNode(void) { return calloc(1, sizeof(Trie)); }
void trieInsert(Trie *root, const char *w) {
for (int i = 0; w[i]; i++) {
int c = w[i] - 'a';
if (!root->child[c]) root->child[c] = trieNode();
root = root->child[c];
}
root->is_end = 1;
}
int trieSearch(Trie *root, const char *w) {
for (int i = 0; w[i]; i++) {
int c = w[i] - 'a';
if (!root->child[c]) return 0;
root = root->child[c];
}
return root->is_end;
}
void autocomplete(Trie *node, char *buf, int depth) {
if (!node) return;
if (node->is_end) { buf[depth] = '\0'; printf(" %s\n", buf); }
for (int i = 0; i < 26; i++) {
if (node->child[i]) {
buf[depth] = 'a' + i;
autocomplete(node->child[i], buf, depth + 1);
}
}
}
void trieAutocomplete(Trie *root, const char *prefix) {
for (int i = 0; prefix[i]; i++) {
int c = prefix[i] - 'a';
if (!root->child[c]) { printf(" (no matches)\n"); return; }
root = root->child[c];
}
char buf[MAX_LEN];
strncpy(buf, prefix, MAX_LEN - 1);
autocomplete(root, buf, (int)strlen(prefix));
}
/* ── Sorted array for range listing ── */
char dict[MAX_WORDS][MAX_LEN];
int dictSize = 0;
int cmpStr(const void *a, const void *b) {
return strcmp((const char *)a, (const char *)b);
}
void dictInsert(const char *w) {
if (dictSize < MAX_WORDS) {
strncpy(dict[dictSize++], w, MAX_LEN - 1);
qsort(dict, dictSize, MAX_LEN, cmpStr);
}
}
void rangeList(const char *lo, const char *hi) {
for (int i = 0; i < dictSize; i++)
if (strcmp(dict[i], lo) >= 0 && strcmp(dict[i], hi) <= 0)
printf(" %s\n", dict[i]);
}
/* ── Main ── */
int main(void) {
const char *words[] = {
"apple","apply","apt","band","banana","cat",
"data","date","define","digit","dog","door"
};
int n = 12;
Trie *root = trieNode();
for (int i = 0; i < n; i++) { trieInsert(root, words[i]); dictInsert(words[i]); }
printf("Exact look-up 'banana': %s\n", trieSearch(root, "banana") ? "Found" : "Not Found");
printf("Exact look-up 'mango' : %s\n", trieSearch(root, "mango") ? "Found" : "Not Found");
printf("Autocomplete 'ap':\n"); trieAutocomplete(root, "ap");
printf("Autocomplete 'da':\n"); trieAutocomplete(root, "da");
printf("Range 'band' to 'date':\n"); rangeList("band", "date");
return 0;
}
