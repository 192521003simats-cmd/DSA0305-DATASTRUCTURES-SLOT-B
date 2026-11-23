#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
typedef struct { int *a; int *tmp; int lo; int hi; int depth; }
Args;
void serial_merge(int a[], int tmp[], int lo, int mid, int hi); /* as before */
void *parallel_sort(void *arg) {
Args *p = (Args *)arg;
if (p->lo >= p->hi) return NULL;
int mid = p->lo + (p->hi - p->lo) / 2;
if (p->depth > 0) {
pthread_t t;
Args left = {p->a, p->tmp, p->lo, mid, p->depth - 1};
Args right = {p->a, p->tmp, mid + 1, p->hi, p->depth - 1};
pthread_create(&t, NULL, parallel_sort, &left);
parallel_sort(&right); /* right half on current thread */
pthread_join(t, NULL);
} else {
/* below threshold: sort serially */
Args left = {p->a, p->tmp, p->lo, mid, 0};
Args right = {p->a, p->tmp, mid + 1, p->hi, 0};
parallel_sort(&left);
parallel_sort(&right);
}
serial_merge(p->a, p->tmp, p->lo, mid, p->hi);
return NULL;
}
