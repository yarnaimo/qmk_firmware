#include QMK_KEYBOARD_H
#include "iolite.h"
#include "str.h"

const PROGMEM il_strmap strmap[] = {
  {.key = IL_W,    .kana = "ei"},
  {.key = IL_R,    .kana = "ai"},
  {.key = IL_X,    .kana = "ou"},
  {.key = IL_V,    .kana = "uu"},
  {.key = IL_PGDN, .kana = ""},
  {.key = IL_END,  .kana = ""},
  {.key = IL_TMB1, .kana = ""},
  {.key = IL_TMB3, .kana = ""},
  {.key = IL_TMB4, .kana = ""},
  {.key = IL_TMB6, .kana = ""},
};

bool process_strmap(uint16_t keycode) {
  il_strmap entry;

  // return true;
  for (int i = 0; i < sizeof strmap / sizeof strmap[0]; i++) {
    memcpy_P(&entry, &strmap[i], sizeof(strmap[i]));
    if (keycode == entry.key) {
      // {
      //   uint8_t ms = 70;
      //   while (ms--) wait_ms(1);
      // }
      send_string(entry.kana);
      return false;
    }
  }

  return true;
}
