#include "ll.h"
#include <assert.h>
#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//I would like to source Darrell Long for providing me with the code below
//However there was a large memory leak in LL_insert in which it wouldnt
//delete the repeated goodspeak structs
ListNode *ll_node_create(GoodSpeak *gs) {
  ListNode *p = (ListNode *)malloc(sizeof(ListNode));
  if (p) {
    p->gs = gs;
    p->next = NIL;
    return p;
  } else {
    return NIL;
  }
}

void ll_node_delete(ListNode *n) {
  if (n->gs != NIL) {
    delete_goodspeak(n->gs);
  }
  free(n);
  return;
}

void ll_delete(ListNode *head) {
  while (head != NIL) {
    ListNode *t = head;
    head = head->next;
    ll_node_delete(t);
  }
  return;
}

ListNode *ll_insert(ListNode **head, GoodSpeak *gs) {
  assert(gs);
  if (ll_lookup(head, gs->old_speak)) {
    delete_goodspeak(gs);
    return *head;
  } else {
    ListNode *n = ll_node_create(gs);
    assert(n);
    n->next = *head;
    return n;
  }
}

ListNode *ll_lookup(ListNode **head, const char *key) {
  count += 1;
  ListNode *t = NIL;
  for (ListNode *n = *head; n != NIL; n = n->next) {
    distance += 1;
    assert(n);
    assert(n->gs);
    assert(n->gs->old_speak);
    if (strcmp(n->gs->old_speak, key) == 0) {
      if (move_to_front && t != NIL) {
        t->next = n->next;
        n->next = *head;
        *head = n;
      }
      return n;
    }
    t = n;
  }
  return NIL;
}

void ll_print(ListNode *n) {
  for (ListNode *t = n; t != NIL; t = t->next) {
    if (t->gs->new_speak == NIL) {
      printf("%s\n", t->gs->old_speak);
    } else {
      printf("%s -> %s\n", t->gs->old_speak, t->gs->new_speak);
    }
  }
  return;
}
