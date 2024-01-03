#ifndef NIL
#define NIL (void *)0
#endif
#include "gs.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

GoodSpeak *make_good_speak(char *oldspeak, char *newspeak) {
  GoodSpeak *g = (GoodSpeak *)malloc(sizeof(GoodSpeak));
  if (g) {
    g->old_speak = strdup(oldspeak);
    if (newspeak == NIL) {
      g->new_speak = NIL;
    } else {
      g->new_speak = strdup(newspeak);
    }
    return g;
  }
  return NIL;
}

void delete_goodspeak(GoodSpeak *g) {
  if (g->old_speak != NIL) {
    free(g->old_speak);
    g->old_speak = NIL;
  }
  if (g->new_speak != NIL) {
    free(g->new_speak);
    g->new_speak = NIL;
  }
  free(g);
  g = NIL;
}
