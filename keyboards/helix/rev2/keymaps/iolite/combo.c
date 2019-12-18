#include QMK_KEYBOARD_H
#include "process_combo.h"
#include "iolite.h"
#include "combo.h"

const PROGMEM il_combomap combomap[] = {
  // [C_AI]  = {.keys = {IL_R, 0},       .kana = "ai"},
  // [C_UU]  = {.keys = {IL_V, 0},       .kana = "uu"},
  // [C_EI]  = {.keys = {IL_W, 0},       .kana = "ei"},
  // [C_OU]  = {.keys = {IL_X, 0},       .kana = "ou"},

  // [C_ATT]  = {.keys = {KC_E, KC_I, 0},       .kana = "altu"},
  // [C_ITT]  = {.keys = {IL_F, IL_D, 0},       .kana = "iltu"},
  // [C_UTT]  = {.keys = {IL_D, IL_S, 0},       .kana = "ultu"},
  // [C_ETT]  = {.keys = {IL_S, IL_A, 0},       .kana = "eltu"},
  // [C_OTT]  = {.keys = {IL_C, IL_X, 0},       .kana = "oltu"},

  // [C_AN]   = {.keys = {IL_TMB1, IL_E, 0},    .kana = "ann"},
  // [C_IN]   = {.keys = {IL_TMB1, IL_F, 0},    .kana = "inn"},
  // [C_UN]   = {.keys = {IL_TMB1, IL_D, 0},    .kana = "unn"},
  // [C_EN]   = {.keys = {IL_TMB1, IL_S, 0},    .kana = "enn"},
  // [C_ON]   = {.keys = {IL_TMB1, IL_C, 0},    .kana = "onn"},

  // [C_LEFT] = {.keys = {IL_J, IL_H, 0},       .kana = SS_TAP(X_LEFT)},
  // [C_UP]   = {.keys = {IL_I, IL_U, 0},       .kana = SS_TAP(X_UP)},
  // [C_DOWN] = {.keys = {IL_K, IL_J, 0},       .kana = SS_TAP(X_DOWN)},
  // [C_RGHT] = {.keys = {IL_L, IL_K, 0},       .kana = SS_TAP(X_RGHT)},

  [C_HOME] = {.keys = {IL_LEFT, IL_TMB6, 0}, .kana = SS_TAP(X_HOME)},
  [C_PGUP] = {.keys = {IL_UP, IL_LEFT, 0},   .kana = SS_TAP(X_PGUP)},
  [C_PGDN] = {.keys = {IL_DOWN, IL_UP, 0},   .kana = SS_TAP(X_PGDN)},
  [C_END]  = {.keys = {IL_RGHT, IL_DOWN, 0}, .kana = SS_TAP(X_END)},

  // [C_YA]   = {.keys = {IL_TMB2, IL_E, 0},    .kana = "ya"},
  // [C_YAI]  = {.keys = {IL_TMB2, IL_R, 0},    .kana = "y"},
  // [C_CIRC] = {.keys = {IL_TMB2, IL_T, 0},    .kana = "^"},
  // [C_SCLN] = {.keys = {IL_TMB2, IL_S, 0},    .kana = ";"},
  // [C_YU]   = {.keys = {IL_TMB2, IL_D, 0},    .kana = "yu"},
  // [C_COLN] = {.keys = {IL_TMB2, IL_F, 0},    .kana = ":"},
  // [C_AT]   = {.keys = {IL_TMB2, IL_G, 0},    .kana = "@"},
  // [C_YOU]  = {.keys = {IL_TMB2, IL_X, 0},    .kana = "y"},
  // [C_YO]   = {.keys = {IL_TMB2, IL_C, 0},    .kana = "yo"},
  // [C_YUU]  = {.keys = {IL_TMB2, IL_V, 0},    .kana = "y"},

  [C_GRV]  = {.keys = {IL_TMB5, IL_U, 0},    .kana = SS_PAIR("``")},
  [C_BRC]  = {.keys = {IL_TMB5, IL_I, 0},    .kana = SS_PAIR("[]")},
  [C_DQT]  = {.keys = {IL_TMB5, IL_O, 0},    .kana = SS_PAIR("\"\"")},
  [C_QUOT] = {.keys = {IL_TMB5, IL_H, 0},    .kana = SS_PAIR("''")},
  [C_PRN]  = {.keys = {IL_TMB5, IL_J, 0},    .kana = SS_PAIR("()")},
  [C_LGT]  = {.keys = {IL_TMB5, IL_K, 0},    .kana = SS_PAIR("<>")},
  [C_CBR]  = {.keys = {IL_TMB5, IL_L, 0},    .kana = SS_PAIR("{}")},

  [C_TILD] = {.keys = {IL_TMB5, IL_SCLN, 0}, .kana = "~"},
  [C_SLSH] = {.keys = {IL_TMB5, IL_M, 0},    .kana = "/"},
  [C_PIPE] = {.keys = {IL_TMB5, IL_COMM, 0}, .kana = "|"},
  [C_BSLS] = {.keys = {IL_TMB5, IL_DOT, 0},  .kana = "\\"},
  [C_3L]   = {.keys = {IL_TMB5, IL_SLSH, 0}, .kana = "///"},
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
  COMBO_ACTION(combomap[4].keys),
  COMBO_ACTION(combomap[5].keys),
  COMBO_ACTION(combomap[6].keys),
  COMBO_ACTION(combomap[7].keys),
  COMBO_ACTION(combomap[8].keys),
  COMBO_ACTION(combomap[9].keys),
  COMBO_ACTION(combomap[10].keys),
  COMBO_ACTION(combomap[11].keys),
  COMBO_ACTION(combomap[12].keys),
  COMBO_ACTION(combomap[13].keys),
  COMBO_ACTION(combomap[14].keys),
  COMBO_ACTION(combomap[15].keys),
  // COMBO_ACTION(combomap[16].keys),
  // COMBO_ACTION(combomap[17].keys),
  // COMBO_ACTION(combomap[18].keys),
  // COMBO_ACTION(combomap[19].keys),
  // COMBO_ACTION(combomap[20].keys),
  // COMBO_ACTION(combomap[21].keys),
  // COMBO_ACTION(combomap[22].keys),
  // COMBO_ACTION(combomap[23].keys),
  // COMBO_ACTION(combomap[24].keys),
  // COMBO_ACTION(combomap[25].keys),
  // COMBO_ACTION(combomap[26].keys),
  // COMBO_ACTION(combomap[27].keys),
  // COMBO_ACTION(combomap[28].keys),
  // COMBO_ACTION(combomap[29].keys),
  // COMBO_ACTION(combomap[30].keys),
  // COMBO_ACTION(combomap[31].keys),
  // COMBO_ACTION(combomap[32].keys),
  // COMBO_ACTION(combomap[33].keys),
  // COMBO_ACTION(combomap[34].keys),
  // COMBO_ACTION(combomap[35].keys),
  // COMBO_ACTION(combomap[36].keys),
  // COMBO_ACTION(combomap[37].keys),
  // COMBO_ACTION(combomap[38].keys),
  // COMBO_ACTION(combomap[39].keys),
  // COMBO_ACTION(combomap[40].keys),
  // COMBO_ACTION(combomap[41].keys),
  // COMBO_ACTION(combomap[42].keys),
  // COMBO_ACTION(combomap[43].keys),
};
