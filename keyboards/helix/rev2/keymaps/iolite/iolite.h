#include QMK_KEYBOARD_H
#include "keymap_jp.h"

#define SS_PAIR(str) str SS_TAP(X_LEFT)

typedef enum iolite_keycodes {
  SP_RAIS = SAFE_RANGE,
  ZH_RAIS,
  // IL_HOME,
  // IL_PGUP,
  // IL_PGDN = SAFE_RANGE,
  // IL_END,
  // IL_TMB1,
  // IL_TMB2,
  // IL_TMB3,

  // IL_TMB4,
  // IL_TMB5,
  // IL_TMB6,
  // IL_LEFT,
  // IL_UP,
  // IL_DOWN,
  // IL_RGHT,
} ILKCS;

// #define IL_SAFE_RANGE SAFE_RANGE+63

#define IL_Q    KC_X
#define IL_W    KC_E
#define IL_E    KC_A
#define IL_R    JP_MHEN
#define IL_T    KC_J
#define IL_Y    KC_F
#define IL_U    KC_G
#define IL_I    KC_K
#define IL_O    KC_H
#define IL_P    KC_B
#define IL_A    KC_C
#define IL_S    KC_O
#define IL_D    KC_U
#define IL_F    KC_I
#define IL_G    KC_L
#define IL_H    KC_D
#define IL_J    KC_T
#define IL_K    KC_S
#define IL_L    KC_N
#define IL_SCLN KC_Z
#define IL_Z    KC_Q
#define IL_X    JP_EQL
#define IL_C    KC_SLSH
#define IL_V    KC_MINS
#define IL_B    KC_V
#define IL_N    KC_Y
#define IL_M    KC_M
#define IL_COMM KC_P
#define IL_DOT  KC_R
#define IL_SLSH KC_W
// #define IL_SHFT KC_SPC
#define IL_LEFT KC_LEFT
#define IL_UP   KC_UP
#define IL_DOWN KC_DOWN
#define IL_RGHT KC_RGHT
