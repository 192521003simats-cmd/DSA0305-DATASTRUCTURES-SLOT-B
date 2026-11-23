#include <stdio.h>
#define V_MAX 50001
#define V 50001
extern int head_arr[V_MAX + 1], adj[], next_e[];
/* Connected components and cycle-detection snippets.
   These depend on head_arr[], next_e[], adj[], V and stdio.h from B1.1. */
int components = 0;
int visited[V_MAX] = {0};
void dfs_component(int u) {
visited[u] = 1;
for (int e = head_arr[u]; e != -1; e = next_e[e])
if (!visited[adj[e]]) dfs_component(adj[e]);
}
for (int v = 0; v < V; v++) {
if (!visited[v]) {
dfs_component(v);
components++;
}
}
printf("Connected components: %d\n", components);
Cycle Detection (DFS with 3-colour marking):
int color[V_MAX]; /* 0=WHITE, 1=GRAY, 2=BLACK */
int has_cycle = 0;
void dfs_cycle(int u) {
color[u] = 1; /* GRAY: in progress */
for (int e = head_arr[u]; e != -1; e = next_e[e]) {
int v = adj[e];
if (color[v] == 1) { has_cycle = 1; return; } /* back
edge */
if (color[v] == 0) dfs_cycle(v);
}
color[u] = 2; /* BLACK: done */
}
