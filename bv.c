// I would like to source myself for this code as I brought this back from
// assignment 5
#include "bv.h"
#include <assert.h>
#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//
// Creates a new BitVector of specified length.
//
// bit_len : The length in bits of the BitVector.
BitVector *bv_create(uint32_t bit_len) {
  BitVector *v;
  v = (BitVector *)malloc(sizeof(BitVector));
  assert(v);
  uint32_t byte_length;
  if (bit_len % 8 != 0) {
    byte_length = (bit_len / 8) + 1;
  } else {
    byte_length = bit_len / 8;
  }
  v->vector = (uint8_t *)calloc(byte_length, sizeof(uint8_t));
  v->length = bit_len;
  return v;
}

//
// Frees memory allocated for a BitVector.
//
// v : The BitVector.
//
void bv_delete(BitVector *v) {
  free(v->vector);
  free(v);
}
//
// Returns the length in bits of the BitVector.
//
// v : The BitVector.
//
uint32_t bv_get_len(BitVector *v) {
  return v->length;
}

//
// Sets the bit at index in the BitVector.
//
// v : The BitVector.
// i : Index of the bit to set.s
void bv_set_bit(BitVector *v, uint32_t i) {
  v->vector[i / 8] |= (0x1 << (i % 8));
  return;
}
//
// Clears the bit at index in the BitVector.
//
// v : The BitVector.
// i : Index of the bit to clear.
//
void bv_clr_bit(BitVector *v, uint32_t i) {
  v->vector[i / 8] &= ~(0x1 << (i % 8));
  return;
}

//
// Gets a bit from a BitVector.
//
// v : The BitVector.
// i : Index of the bit to get.
//
uint8_t bv_get_bit(BitVector *v, uint32_t i) {
  uint8_t bit = (v->vector[i / 8] & (0x1 << (i % 8))) >> (i % 8);
  return bit;
}

//
// Sets all bits in a BitVector.
//
// v : The BitVector.
//
void bv_set_all_bits(BitVector *v) {
  uint32_t byte_length;
  if (v->length % 8 != 0) {
    byte_length = (v->length / 8) + 1;
  } else {
    byte_length = v->length / 8;
  }
  memset(v->vector, 0xff, byte_length);
}
