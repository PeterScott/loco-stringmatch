#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

void kmp_table(char *needle, int16_t *T, size_t len);
int kmp_search(char *haystack, char *needle, int16_t *T, size_t needle_len, size_t haystack_len);
int kmp_search3(char *haystack, size_t haystack_len);
int kmp_search_inl(char *haystack, size_t haystack_len);

int main(void) {
  char needle[7] = {'a', 'b', 'c', 'd', 'a', 'b', 'd'};
  int16_t T[7];
  char haystack[] = "abracadabra abcdefgababcdabd vooleyfoo"; /* 21 */
  
  int i;

  //  kmp_table(needle, T, 7);
  int idx = kmp_search3(haystack, strlen(haystack));
  printf("idx = %i\n", idx);
  idx = kmp_search_inl(haystack, strlen(haystack));
  printf("idx = %i\n", idx);

  int j, len = strlen(haystack);
  for (j = 0; j < 1000000000; j++) idx = kmp_search_inl(haystack, len);
  //for (j = 0; j < 1000000000; j++) kmp_search3(haystack, len);

  return 0;
}
