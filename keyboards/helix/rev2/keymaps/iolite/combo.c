#include QMK_KEYBOARD_H
#include "process_combo.h"
#include "iolite.h"
#include "combo.h"

const PROGMEM il_combomap combomap[] = {
  [C_HOME] = {.keys = {IL_LEFT, JP_HENK, 0}, .kana = SS_TAP(X_HOME)},
  [C_PGUP] = {.keys = {IL_UP, KC_R, 0}, .kana = SS_TAP(X_PGUP)},
  [C_PGDN] = {.keys = {IL_DOWN, IL_LEFT, 0}, .kana = SS_TAP(X_PGDN)},
  [C_END]  = {.keys = {IL_RGHT, IL_DOWN, 0}, .kana = SS_TAP(X_END)},
};

void process_combomap(uint8_t combo_index) {
  char kana[5] = {0};
  memcpy_P(&kana, &combomap[combo_index].kana, sizeof combomap[combo_index].kana);
  send_string(kana);
}

combo_t key_combos[COMBO_COUNT] = {
  COMBO_ACTION(combomap[0].keys),
  COMBO_ACTION(combomap[1].keys),
  COMBO_ACTION(combomap[2].keys),
  COMBO_ACTION(combomap[3].keys),
};
