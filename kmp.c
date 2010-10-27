/* haystackimple Knuth-Morris-Pratt string search code */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

void kmp_table(char *needle, int16_t *T, size_t len) {
  int pos = 2, cnd = 0;
  T[0] = -1;
  T[1] = 0;

  while (pos < len) {
    if (needle[pos - 1] == needle[cnd]) T[pos++] = ++cnd;
    else if (cnd > 0) cnd = T[cnd];
    else T[pos++] = 0;
  }
}

int kmp_search(char *haystack, char *needle, int16_t *T, size_t needle_len, size_t haystack_len) {
  int needle_pos = 0, haystack_pos = 0;

  /* While we're within the haystack */
  while (haystack_pos < haystack_len) {
    /* While we have a mismatch, jump in the table until we find a match. */
    while (needle_pos > -1 && needle[needle_pos] != haystack[haystack_pos])
      needle_pos = T[needle_pos];
    
    /* Extend the current match (guaranteed by previous chunk) */
    needle_pos++; haystack_pos++;

    /* Check to see if this is a whole match */
    if (needle_pos >= needle_len) /* Found it! */
      return haystack_pos - needle_pos;
  }

  return -1;			/* Unsuccessful */
}

// -1 0 0 0 0 1 2

#define SAVEREGS asm("pushq %rax\n\tpushq %rbx\n\tpushq %rcx\n\tpushq %rdx\n\t")
#define RESTREGS asm("popq %rdx\n\tpopq %rcx\n\tpopq %rbx\n\tpopq %rax\n\t")

void fool9(void) { SAVEREGS; printf("fool 9\n"); RESTREGS; }
void fool0(void) { SAVEREGS; printf("fool 0\n"); RESTREGS; }
void fool1(void) { SAVEREGS; printf("fool 1\n"); RESTREGS; }
void fool2(void) { SAVEREGS; printf("fool 2\n"); RESTREGS; }
void fool3(void) { SAVEREGS; printf("fool 3\n"); RESTREGS; }
void fool4(void) { SAVEREGS; printf("fool 4\n"); RESTREGS; }
void fool5(void) { SAVEREGS; printf("fool 5\n"); RESTREGS; }
void fool6(void) { SAVEREGS; printf("fool 6\n"); RESTREGS; }

int kmp_search3(char *haystack, size_t haystack_len) {
  int haystack_pos = 0;

  goto needle0;

 needle_minus_one:
  // fool9();
  haystack_pos++; if (haystack_pos >= haystack_len) goto bad_end;

 needle0:
  //  fool0();
  if ('a' != haystack[haystack_pos]) goto needle_minus_one;
  haystack_pos++; if (haystack_pos >= haystack_len) goto bad_end;
  
 needle1:
  //  fool1();
  if ('b' != haystack[haystack_pos]) goto needle0;
  haystack_pos++; if (haystack_pos >= haystack_len) goto bad_end;
  
 needle2:
  //  fool2();
  if ('c' != haystack[haystack_pos]) goto needle0;
  haystack_pos++; if (haystack_pos >= haystack_len) goto bad_end;
  
 needle3:
  // fool3();
  if ('d' != haystack[haystack_pos]) goto needle0;
  haystack_pos++; if (haystack_pos >= haystack_len) goto bad_end;
  
 needle4:
  // fool4();
  if ('a' != haystack[haystack_pos]) goto needle0;
  haystack_pos++; if (haystack_pos >= haystack_len) goto bad_end;
  
 needle5:
  // fool5();
  if ('b' != haystack[haystack_pos]) goto needle1;
  haystack_pos++; if (haystack_pos >= haystack_len) goto bad_end;
  
 needle6:
  // fool6();
  if ('d' != haystack[haystack_pos]) goto needle2;
  haystack_pos++; if (haystack_pos >= haystack_len) goto bad_end;

  /* We found it! */
  return haystack_pos - 7;

 bad_end:
  return -1;			/* Unsuccessful */
}

int kmp_search_inl(char *haystack, size_t haystack_len) {
  int64_t haystack_pos;

  asm ("xorq %%rax, %%rax\n\t"
       "xorq %1, %1\n\t"
       "jmp 0f\n\t"

       "9:\n\t"
       //       "call _fool9\n\t"
       "incq %1\n\t"
       "cmpq %2, %1\n\t"
       "jge 7f\n\t"

       "0:\n\t"
       //       "call _fool0\n\t"
       "movb (%3, %1), %%al\n\t"
       "cmpb $97, %%al\n\t"
       "jne 9b\n\t"
       "incq %1\n\t"
       "cmpq %2, %1\n\t"
       "jge 7f\n\t"

       "1:\n\t"
       //       "call _fool1\n\t"
       "movb (%3, %1), %%al\n\t"
       "cmpb $98, %%al\n\t"
       "jne 0b\n\t"
       "incq %1\n\t"
       "cmpq %2, %1\n\t"
       "jge 7f\n\t"
       
       "2:\n\t"
       //       "call _fool2\n\t"
       "movb (%3, %1), %%al\n\t"
       "cmpb $99, %%al\n\t"
       "jne 0b\n\t"
       "incq %1\n\t"
       "cmpq %2, %1\n\t"
       "jge 7f\n\t"

       "3:\n\t"
       //       "call _fool3\n\t"
       "movb (%3, %1), %%al\n\t"
       "cmpb $100, %%al\n\t"
       "jne 0b\n\t"
       "incq %1\n\t"
       "cmpq %2, %1\n\t"
       "jge 7f\n\t"

       "4:\n\t"
       //       "call _fool4\n\t"
       "movb (%3, %1), %%al\n\t"
       "cmpb $97, %%al\n\t"
       "jne 0b\n\t"
       "incq %1\n\t"
       "cmpq %2, %1\n\t"
       "jge 7f\n\t"

       "5:\n\t"
       //              "call _fool5\n\t"
       "movb (%3, %1), %%al\n\t"
       "cmpb $98, %%al\n\t"
       "jne 1b\n\t"
       "incq %1\n\t"
       "cmpq %2, %1\n\t"
       "jge 7f\n\t"

       "6:\n\t"
       //       "call _fool6\n\t"
       "movb (%3, %1), %%al\n\t"
       "cmpb $100, %%al\n\t"
       "jne 2b\n\t"
       "incq %1\n\t"
       "cmpq %2, %1\n\t"
       "jge 7f\n\t"

       /* Found it! subtract 7 from haystack_pos and goto end */
       "subq $7, %0\n\t"
       "jmp 8f\n\t"
       
       /* Didn't find it. Put -1 into haystack_pos, goto end */
       "7:\n\t"
       "movq $-1, %0\n\t"
       "jmp 8f\n\t"

       "11:\n\t"		/* for debugging only */
       "movq $42, %0\n\t"

       "8:\n\t"
       : "=b" (haystack_pos)	/* output %0 */
       : "b" (haystack_pos),	/* input %1 */
	 "c" (haystack_len),	/* input %2 */
	 "d" (haystack)	/* input %3 */
       : "%rax"			/* clobber list */
       );

  return haystack_pos;
}
