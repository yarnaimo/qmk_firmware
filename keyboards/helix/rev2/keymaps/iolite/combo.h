#include QMK_KEYBOARD_H
#include "../../rev2.h"

typedef struct {
  uint16_t keys[3];
  char kana[5];
} il_combomap;

void process_combomap(uint8_t);

typedef enum combo_codes {
  C_HOME,
  C_PGUP,
  C_PGDN,
  C_END,
} COMBOKCS;
