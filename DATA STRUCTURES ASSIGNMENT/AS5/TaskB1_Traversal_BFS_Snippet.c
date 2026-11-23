#include <stdio.h>
#include <string.h>
#define V_MAX 50001
#define E_MAX 240001
int head_arr[V_MAX+1], adj[E_MAX], next_e[E_MAX], edge_cnt = 0;
int dist[V_MAX], parent_bfs[V_MAX], visited[V_MAX];
void add_edge(int u, int v) {
adj[edge_cnt] = v;
next_e[edge_cnt] = head_arr[u];
head_arr[u] = edge_cnt++;
}
void bfs(int src, int V) {
int queue[V_MAX], h=0, t=0;
memset(dist, -1, sizeof(int)*V);
dist[src]=0; parent_bfs[src]=-1; queue[t++]=src;
while (h<t) {
int u=queue[h++];
for (int e=head_arr[u]; e!=-1; e=next_e[e]) {
int w=adj[e];
if (dist[w]==-1) {
dist[w]=dist[u]+1;
parent_bfs[w]=u;
queue[t++]=w;
}
}
}
}
/* Metro: Airport(0)-Guindy(1)-Saidapet(2)-Central(3)
Egmore(4)-Vadapalani(5)-Koyambedu(6) */
/* Verification: BFS from Airport(0) to Koyambedu(6) = 3 stops */
/* Path: Airport → Guindy → Vadapalani → Koyambedu */
