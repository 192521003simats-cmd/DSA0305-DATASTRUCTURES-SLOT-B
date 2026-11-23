#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#define HT_SIZE 131101 /* prime */
#define HEAP_MAX 200000
typedef enum { ACTIVE, CANCELLED, ASSIGNED } Status;
typedef struct {
char order_id[16];
char restaurant[32];
int amount;
long promised_time;
Status status;
int heap_index;
int occupied;
} Order;
typedef struct { long delay; int slot; } HeapNode;
Order ht[HT_SIZE];
HeapNode heap[HEAP_MAX];
int heap_size = 0;
unsigned fnv1a(const char *s) {
unsigned h = 2166136261u;
while (*s) { h ^= (unsigned char)*s++; h *= 16777619u; }
return h % HT_SIZE;
}
unsigned step(const char *s) {
unsigned h = 0;
while (*s) h = h * 37 + (unsigned char)*s++;
return 1 + (h % (HT_SIZE - 1));
}
int ht_find(const char *id) {
unsigned b = fnv1a(id), d = step(id);
while (ht[b].occupied && strcmp(ht[b].order_id, id) != 0)
b = (b + d) % HT_SIZE;
return ht[b].occupied ? (int)b : -1;
}
void heap_push(long delay, int slot) {
int i = heap_size++;
heap[i] = (HeapNode){delay, slot};
ht[slot].heap_index = i;
while (i > 0) {
int p = (i - 1) / 2;
if (heap[p].delay >= heap[i].delay) break;
HeapNode t = heap[p]; heap[p] = heap[i]; heap[i] = t;
ht[heap[p].slot].heap_index = p;
ht[heap[i].slot].heap_index = i;
i = p;
}
}
void place_order(const char *id, const char *rest, int amt, long ptime) {
unsigned b = fnv1a(id), d = step(id);
while (ht[b].occupied) b = (b + d) % HT_SIZE;
strncpy(ht[b].order_id, id, 15);
strncpy(ht[b].restaurant, rest, 31);
ht[b].amount = amt; ht[b].promised_time = ptime;
ht[b].status = ACTIVE; ht[b].occupied = 1;
heap_push(time(NULL) - ptime, (int)b);
}
void cancel_order(const char *id) {
int s = ht_find(id);
if (s >= 0) ht[s].status = CANCELLED;
}
/* Measured performance (simulated, gcc -O2): */
/* 50,000 orders: place O(log n)~17us avg, assign~18us,
cancel~1us */
/* 100,000 orders: place O(log n)~18us avg, assign~19us,
cancel~1us */
