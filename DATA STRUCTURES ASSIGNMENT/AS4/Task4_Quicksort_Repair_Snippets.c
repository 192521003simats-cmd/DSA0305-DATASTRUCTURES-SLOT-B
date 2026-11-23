#include <stdio.h>
#include <stdlib.h>
void swap(int *a, int *b) { int t = *a; *a = *b; *b = t; }
/* Median-of-three: returns index of median of a[lo], a[mid],
a[hi] */
int median3(int a[], int lo, int hi) {
int mid = lo + (hi - lo) / 2;
if (a[lo] > a[mid]) swap(&a[lo], &a[mid]);
if (a[lo] > a[hi]) swap(&a[lo], &a[hi]);
if (a[mid] > a[hi]) swap(&a[mid], &a[hi]);
swap(&a[mid], &a[hi - 1]); /* hide pivot */
return hi - 1;
}
void quick_fixed(int a[], int lo, int hi) {
while (lo < hi) {
int pivotIdx = median3(a, lo, hi);
int p = a[pivotIdx], i = lo - 1;
for (int j = lo; j < hi; j++)
if (a[j] <= p) { i++; swap(&a[i], &a[j]); }
swap(&a[i + 1], &a[hi]);
int pi = i + 1;
/* Recurse on smaller partition; loop on larger (limits
stack to O(log n)) */
if (pi - lo < hi - pi) {
quick_fixed(a, lo, pi - 1);
lo = pi + 1;
} else {
quick_fixed(a, pi + 1, hi);
hi = pi - 1;
}
}
}
/* Solution 2: Stable merge-sort merge function. */
void merge_stable(int a[], int lo, int mid, int hi, int tmp[]) {
int i = lo, j = mid + 1, k = lo;
while (i <= mid && j <= hi)
tmp[k++] = (a[i] <= a[j]) ? a[i++] : a[j++]; /* <= for stability */
while (i <= mid) tmp[k++] = a[i++];
while (j <= hi) tmp[k++] = a[j++];
for (int x = lo; x <= hi; x++) a[x] = tmp[x];
}
