#include QMK_KEYBOARD_H
#include "keymap_jp.h"

#define SS_PAIR(str) str SS_TAP(X_LEFT)

typedef enum iolite_keycodes {
  SP_RAIS = SAFE_RANGE,
  ZH_RAIS,

  LR_BRC,
  LR_PRN,
  LR_T,
  LR_CBR,
} ILKCS;

// #define IL_SAFE_RANGE SAFE_RANGE+63
