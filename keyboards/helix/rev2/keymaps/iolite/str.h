#include QMK_KEYBOARD_H
#include "../../rev2.h"

typedef struct {
  uint16_t key;
  char kana[5];
} il_strmap;

bool process_strmap(uint16_t);
