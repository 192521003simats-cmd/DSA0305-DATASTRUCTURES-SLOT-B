#include <stdio.h>
#define MAX 32
typedef struct { int severity; int patient; } Case;
Case heap[MAX];
int size = 0;
void swap(Case *a, Case *b) { Case t = *a; *a = *b; *b = t; }
void push(int severity, int patient) {
if (size == MAX) return;
heap[size] = (Case){severity, patient};
int i = size++;
/* TODO 1 – completed: sift up */
while (i > 0) {
int p = (i - 1) / 2;
if (heap[p].severity >= heap[i].severity) break;
swap(&heap[p], &heap[i]);
i = p;
}
}
Case pop(void) {
Case top = heap[0];
heap[0] = heap[--size];
int i = 0;
/* TODO 2 – completed: sift down */
for (;;) {
int l = 2*i+1, r = 2*i+2, s = i;
if (l < size && heap[l].severity > heap[s].severity) s =
l;
if (r < size && heap[r].severity > heap[s].severity) s =
r;
if (s == i) break;
swap(&heap[i], &heap[s]);
i = s;
}
return top;
}
int main(void) {
int sev[] = {3, 9, 5, 7, 1, 8};
for (int p = 0; p < 6; p++) push(sev[p], 101 + p);
while (size) {
Case c = pop();
printf("P%d(%d) ", c.patient, c.severity);
}
printf("\n");
return 0;
}
