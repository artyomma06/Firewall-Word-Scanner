//I would like to give credit to Eugene Chow and Darrell Long as I am using
//some code modified from their work. I took the lexical analyzer from a
//piazza post by eugene and I used both the printing conditions and the linked
//list code from Darrell Long

#ifndef NIL
#define NIL (void *)0
#endif
#include "bf.h"
#include "gs.h"
#include "hash.h"
#include "ll.h"
#include <getopt.h>
#include <inttypes.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

uint64_t countBF;
uint32_t distance;
uint32_t count;
bool move_to_front;
extern FILE *yyin;
extern char *yytext;
extern int yylex(void);
extern int yylex_destroy(void);

int main(int argc, char **argv) {
  uint32_t text = 0;
  uint32_t words = 0;
  uint32_t trans = 0;
  uint32_t pos = 0;
  uint32_t falsepos = 0;
  int c;
  move_to_front = true;
  bool goodoption = false;
  bool badoption = false;
  bool suppress = false;
  int32_t condition = 0;
  uint32_t hash_size = 10000;
  uint32_t bloom_size = 1048576;
  while ((c = getopt(argc, argv, "smbh:f:")) != -1) {
    if (c == 's') {
      suppress = true;
    }
    if (c == 'm') {
      move_to_front = true;
    }
    if (c == 'b') {
      move_to_front = false;
    }
    if (c == 'h') {
      condition = atoi(optarg);
      if (condition < 0) {
        printf("error negative argument \n");
        return 0;
      }
      hash_size = condition;
    }
    if (c == 'f') {
      condition = atoi(optarg);
      if (condition < 0) {
        printf("error negative argument \n");
        return 0;
      }
      bloom_size = condition;
    }
  }
  uint64_t lenBF = bloom_size;
  BloomFilter *blm = bf_create(bloom_size);
  HashTable *h = ht_create(hash_size);
  yyin = fopen("newspeak.txt", "r");
  while (yylex() != EOF) {
    char *oldspeak = strdup(yytext);
    yylex();
    char *newspeak = strdup(yytext);
    bf_insert(blm, oldspeak);
    GoodSpeak *spk = make_good_speak(oldspeak, newspeak);
    ht_insert(h, spk);
    free(oldspeak);
    free(newspeak);
    words += 2;
  }
  fclose(yyin);
  yyin = fopen("badspeak.txt", "r");
  while (yylex() != EOF) {
    char *oldspeak = strdup(yytext);
    char *newspeak = NIL;
    bf_insert(blm, oldspeak);
    GoodSpeak *spk = make_good_speak(oldspeak, newspeak);
    ht_insert(h, spk);
    free(oldspeak);
    words += 1;
  }
  fclose(yyin);
  ListNode *oldnew = NIL;
  ListNode *bad = NIL;
  yyin = stdin;
  while (yylex() != EOF) {
    text += 1;
    char *yourspeak = strdup(yytext);
    if (bf_probe(blm, yourspeak)) {
      pos += 1;
      if (ht_lookup(h, yourspeak) != NIL) {
        if (ht_lookup(h, yourspeak)->gs->new_speak == NIL) {
          trans += 1;
          char *temp_one = strdup(ht_lookup(h, yourspeak)->gs->old_speak);
          char *temp_two = NIL;
          GoodSpeak *spk = make_good_speak(temp_one, temp_two);
          bad = ll_insert(&bad, spk);
          badoption = true;
          free(temp_one);
        } else {
          char *temp_one = strdup(ht_lookup(h, yourspeak)->gs->old_speak);
          char *temp_two = strdup(ht_lookup(h, yourspeak)->gs->new_speak);
          GoodSpeak *spk = make_good_speak(temp_one, temp_two);
          oldnew = ll_insert(&oldnew, spk);
          goodoption = true;
          free(temp_one);
          free(temp_two);
        }
      } else {
        falsepos += 1;
      }
    }
    free(yourspeak);
  }
  // I would like to source darrell long for these different text options.
  if (!badoption && !suppress && goodoption) {
    printf("Dear Comrade,\n\n");
    printf("Submitting your text helps to preserve feelings and prevent\n");
    printf("badthink. Some of the words that you used are not goodspeak.\n");
    printf("The list shows how to turn the oldspeak words into newspeak.\n\n");
    ll_print(oldnew);
  }
  if (badoption && !suppress) {
    printf("Dear Comrade,\n\n");
    printf("You have chosen to use degenerate words that may cause hurt\n");
    printf("feelings or cause your comrades to think unpleasant thoughts.\n");
    printf("This is doubleplus bad. To correct your wrongthink and\n");
    printf("save community consensus we will be sending you to joycamp\n");
    printf("administered by Miniluv.\n");
    printf("\nYour errors:\n\n");
    ll_print(bad);
    if (goodoption) {
      printf("\nThink on these words during your vacation!\n\n");
      ll_print(oldnew);
    }
  }
  if (suppress && count > 0) {
    printf(
        "Seeks %u, Average %lf, ", distance, (double)distance / (double)count);
    printf("Dictionary %u, Translations %u, Text %u, ", words, trans, text);
    printf("Densities: %lf, %lf\n", countBF / (double)lenBF,
        countBF / (double)lenBF);
    printf("False positives: %u, %lf\n ", falsepos, falsepos / (double)pos);
  }
  if (oldnew != NIL) {
    ll_delete(oldnew);
  }
  if (bad != NIL) {
    ll_delete(bad);
  }
  ht_delete(h);
  bf_delete(blm);
  yylex_destroy();
  return 0;
}
