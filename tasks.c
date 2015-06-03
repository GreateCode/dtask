#include <stdio.h>
#include "dtask.h"

#define DEBUG 0

#if DEBUG
#define debugf(args...) printf(args)
#else
#define debugf(...)
#endif

DTASK(output35, int) {
  const combine35_t *x = &DGET(combine35);
  printf("%d * 3 == %d * 5 == %d\n", x->m3, x->m5, x->m3 * x->m5);
  return true;
}

DTASK(output57, int) {
  const combine57_t *x = &DGET(combine57);
  printf("%d * 5 == %d * 7 == %d\n", x->m5, x->m7, x->m5 * x->m7);
  return true;
}

DTASK(output357, int) {
  const combine357_t *x = &DGET(combine357);
  printf("%d * 3 == %d * 5 == %d * 7 == %d\n", x->m3, x->m5, x->m7, x->m3 * x->m5 * x->m7);
  return true;
}

DTASK(combine357, struct { int m3, m5, m7; }) {
  const combine35_t *m35 = &DGET(combine35);
  int m7 = DGET(mod_seven);
  if(DTASK_AND(COMBINE35 | MOD_SEVEN)) {
    combine357.m3 = m35->m3;
    combine357.m5 = m35->m5;
    combine357.m7 = m7;
    return true;
  } else {
    return false;
  }
}

DTASK(combine35, struct { int m3, m5; }) {
  int m3 = DGET(mod_three);
  int m5 = DGET(mod_five);
  if(DTASK_AND(MOD_THREE | MOD_FIVE)) {
    combine35.m3 = m3;
    combine35.m5 = m5;
    return true;
  } else {
    return false;
  }
}

DTASK(combine57, struct { int m5, m7; }) {
  int m5 = DGET(mod_five);
  int m7 = DGET(mod_seven);
  if(DTASK_AND(MOD_FIVE | MOD_SEVEN)) {
    combine57.m5 = m5;
    combine57.m7 = m7;
    return true;
  } else {
    return false;
  }
}

DTASK(mod_three, int) {
  int x = DGET(count);
  if(x % 3 != 0) return false;
  mod_three = x / 3;
  debugf("mod_three(%d)\n", x);
  return true;
}

DTASK(mod_five, int) {
  int x = DGET(count);
  if(x % 5 != 0) return false;
  mod_five = x / 5;
  debugf("mod_five(%d)\n", x);
  return true;
}

DTASK(mod_seven, int) {
  int x = DGET(count);
  if(x % 7 != 0) return false;
  mod_seven = x / 7;
  debugf("mod_seven(%d)\n", x);
  return true;
}

DTASK(count, int) {
  int x = DGET(count);
  count = x + 1;
  return true;
}
