#include <stdio.h>
#include <string.h>
#define TABLE_SIZE 1009 /* prime near 1000 */
unsigned hash_good(const char *s) {
unsigned h = 5381;
while (*s) h = h * 31 + (unsigned char)*s++;
return h % TABLE_SIZE;
}
unsigned hash_bad(const char *s) {
return ((unsigned char)s[0] + (unsigned char)s[1]) %
TABLE_SIZE;
}
