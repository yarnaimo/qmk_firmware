#include QMK_KEYBOARD_H
#include "../../rev2.h"

typedef struct {
  uint16_t keys[3];
  char kana[5];
} il_combomap;

void process_combomap(uint8_t);

typedef enum combo_codes {
  // C_AI,
  // C_UU,
  // C_EI,
  // C_OU,

  C_ATT,
  C_ITT,
  C_UTT,
  C_ETT,
  C_OTT,

  C_AN,
  C_IN,
  C_UN,
  C_EN,
  C_ON,

  // C_LEFT,
  // C_UP,
  // C_DOWN,
  // C_RGHT,

  C_HOME,
  C_PGUP,
  C_PGDN,
  C_END,

  C_YA,
  C_YAI,
  C_CIRC,
  C_SCLN,
  C_YU,
  C_COLN,
  C_AT,
  C_YOU,
  C_YO,
  C_YUU,

  C_GRV,
  C_BRC,
  C_DQT,
  C_QUOT,
  C_PRN,
  C_LGT,
  C_CBR,

  C_TILD,
  C_SLSH,
  C_PIPE,
  C_BSLS,
  C_3L,
} COMBOKCS;
