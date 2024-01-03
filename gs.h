#ifndef NIL
#define NIL (void *)0
#endif

#ifndef __GS_H__
#define __GS_H__

#include <stdbool.h>

typedef struct GoodSpeak {
  char *old_speak;
  char *new_speak;
} GoodSpeak;

GoodSpeak *make_good_speak(char *oldspeak, char *newspeak);

void delete_goodspeak(GoodSpeak *w);

#endif
