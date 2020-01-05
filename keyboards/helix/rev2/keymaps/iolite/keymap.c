#include QMK_KEYBOARD_H
#include "bootloader.h"
#include "process_combo.h"
#ifdef PROTOCOL_LUFA
  #include "lufa.h"
  #include "split_util.h"
#endif
#ifdef SSD1306OLED
  // #include "oled.h"
#endif

#if !defined(__AVR__)
  #include <string.h>
  #define memcpy_P(des, src, len) memcpy(des, src, len)
#endif

#include "keymap_jp.h"
#include <sendstring_jis.h>
#include "iolite.h"
#include "combo.h"

// #ifdef SSD1306OLED
// void matrix_init_keymap(void) {
//   //SSD1306 OLED init, make sure to add #define SSD1306OLED in config.h
//   iota_gfx_init(!has_usb());   // turns on the display
// }

// void matrix_scan_user(void) {
//   iota_gfx_task();  // this is what updates the display continuously
// }
// #endif

enum keymap_layers {
  _IOLITE, // 薙刀式入力レイヤー
  _RAISE,
};

#define CTLTB CTL_T(KC_TAB)
#define GUITB GUI_T(KC_TAB)
#define ABLS    LALT(KC_BSLS)
#define CMDENT  CMD_T(KC_ENT)
#define SFTSPC  LSFT_T(KC_SPC)
#define CTLSPC  CTL_T(KC_SPC)
#define ALTSPC  ALT_T(KC_SPC)
#define ALTENT  ALT_T(KC_ENT)
#define CTLBS   CTL_T(KC_BSPC)
#define CTLENT  CTL_T(KC_ENT)

#define C_Z LCTL(KC_Z)
#define C_X LCTL(KC_X)
#define C_C LCTL(KC_C)
#define C_V LCTL(KC_V)
#define C_SLSH LCTL(KC_SLSH)
#define CS_Z LCTL(LSFT(KC_Z))
#define CS_I LCTL(LSFT(KC_I))
#define MOZH_MH LT(JP_MHEN)
#define S_COLN SFT_T(JP_COLN)
#define A_ZHTG ALT_T(JP_ZHTG)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_IOLITE] = LAYOUT(
    KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                      KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_DEL,  \
    KC_TAB,  IL_Q,    IL_W,    IL_E,    IL_R,    IL_T,                      IL_Y,    IL_U,    IL_I,    IL_O,    IL_P,    KC_BSPC, \
    A_ZHTG,  IL_A,    IL_S,    IL_D,    IL_F,    IL_G,                      IL_H,    IL_J,    IL_K,    IL_L,    IL_SCLN, KC_ENT,  \
    KC_LSFT, IL_Z,    IL_X,    IL_C,    IL_V,    IL_B,    C_C,     C_Z,     IL_N,    IL_M,    IL_COMM, IL_DOT,  KC_UP,   JP_COLN,  \
    KC_LCTL, KC_LGUI, _______, KC_CAPS, JP_MHEN, KC_COMM, SP_RAIS, SP_RAIS, KC_DOT,  IL_SLSH, JP_HENK, KC_LEFT, KC_DOWN, KC_RGHT  \
  ),

  [_RAISE] = LAYOUT(
    _______, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,                     KC_PSCR, KC_NLCK, KC_PSLS, KC_PAST, KC_PMNS, _______, \
    _______, KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,                    KC_MUTE, KC_P7,   KC_P8,   KC_P9,   KC_PPLS, _______, \
    _______, KC_F11,  KC_F12,  _______, CS_I,    C_SLSH,                    KC_PAUS, KC_P4,   KC_P5,   KC_P6,   KC_PENT, _______, \
    _______, _______, _______, _______, _______, C_X,     C_V,     CS_Z,    KC_INS,  KC_P1,   KC_P2,   KC_P3,   KC_PDOT, _______, \
    _______, _______, _______, RESET,   AG_SWAP, AG_NORM, _______, _______, KC_P0,   KC_P0,   _______, _______, _______, _______  \
  ),
};

int RGB_current_mode;

void persistent_default_layer_set(uint16_t default_layer) {
  eeconfig_update_default_layer(default_layer);
  default_layer_set(default_layer);
}

// Setting ADJUST layer RGB back to default
void update_tri_layer_RGB(uint8_t layer1, uint8_t layer2, uint8_t layer3) {
  if (IS_LAYER_ON(layer1) && IS_LAYER_ON(layer2)) {
    layer_on(layer3);
  } else {
    layer_off(layer3);
  }
}

// void matrix_init_user(void) {
//   // 薙刀式
//   set_iolite(_IOLITE);
//   #ifdef IOLITE_EDIT_MAC
//   set_unicode_input_mode(UC_OSX);
//   #endif
//   #ifdef IOLITE_EDIT_WIN
//   set_unicode_input_mode(UC_WINC);
//   #endif
//   // 薙刀式

//   #ifdef RGBLIGHT_ENABLE
//     RGB_current_mode = rgblight_config.mode;
//   #endif
//   //SSD1306 OLED init, make sure to add #define SSD1306OLED in config.h
//   #ifdef SSD1306OLED
//       iota_gfx_init(!has_usb());   // turns on the display
//   #endif
// }

// //SSD1306 OLED update loop, make sure to add #define SSD1306OLED in config.h
// #ifdef SSD1306OLED

// // When add source files to SRC in rules.mk, you can use functions.
// const char *read_layer_state(void);
// const char *read_logo(void);
// void set_keylog(uint16_t keycode, keyrecord_t *record);
// const char *read_keylog(void);
// const char *read_keylogs(void);

// // const char *read_mode_icon(bool swap);
// // const char *read_host_led_state(void);
// // void set_timelog(void);
// // const char *read_timelog(void);

// void matrix_scan_user(void) {
//    iota_gfx_task();
// }

// void matrix_render_user(struct CharacterMatrix *matrix) {
//   if (is_master) {
//     // If you want to change the display of OLED, you need to change here
//     matrix_write_ln(matrix, read_layer_state());
//     matrix_write_ln(matrix, read_keylog());
//     matrix_write_ln(matrix, read_keylogs());
//     //matrix_write_ln(matrix, read_mode_icon(keymap_config.swap_lalt_lgui));
//     //matrix_write_ln(matrix, read_host_led_state());
//     //matrix_write_ln(matrix, read_timelog());
//   } else {
//     matrix_write(matrix, read_logo());
//   }
// }

// void matrix_update(struct CharacterMatrix *dest, const struct CharacterMatrix *source) {
//   if (memcmp(dest->display, source->display, sizeof(dest->display))) {
//     memcpy(dest->display, source->display, sizeof(dest->display));
//     dest->dirty = true;
//   }
// }

// void iota_gfx_task_user(void) {
//   struct CharacterMatrix matrix;
//   matrix_clear(&matrix);
//   matrix_render_user(&matrix);
//   matrix_update(&display, &matrix);
// }
// #endif//SSD1306OLED

// static bool underglow = false;

// void update_led() {
//   if (layer_state_is(_LOWER) && !isLeftHand) {
//     // rgblight_setrgb_at(0, 0, 200, 7);
//     rgblight_sethsv_at(200, 100, 255, 15);
//     rgblight_sethsv_at(200, 100, 255, 16);
//     rgblight_sethsv_at(200, 100, 255, 17);
//     rgblight_sethsv_at(200, 100, 255, 18);
//     rgblight_sethsv_at(200, 100, 255, 19);
//     rgblight_sethsv_at(200, 100, 255, 20);
//     rgblight_sethsv_at(200, 100, 255, 21);
//     rgblight_sethsv_at(200, 100, 255, 22);
//     rgblight_sethsv_at(200, 100, 255, 23);
//   }
//   if (layer_state_is(_RAISE) && !isLeftHand) {
//     rgblight_sethsv_at(200, 100, 255, 11);
//     rgblight_sethsv_at(200, 100, 255, 16);
//     rgblight_sethsv_at(200, 100, 255, 17);
//     rgblight_sethsv_at(200, 100, 255, 19);
//   }
//   if (!layer_state_is(_LOWER) && !layer_state_is(_RAISE)) {
//     rgblight_sethsv_range(0, 0, 0, 6, 27);
//   }
//   if (iolite_state()) {
//     rgblight_sethsv_at(200, 200, 255, 6);
//     rgblight_sethsv_at(200, 200, 255, 13);
//     rgblight_sethsv_at(200, 200, 255, 14);
//   } else {
//     rgblight_sethsv_at(0, 0, 0, 6);
//     rgblight_sethsv_at(0, 0, 0, 13);
//     rgblight_sethsv_at(0, 0, 0, 14);
//   }
//   if (underglow) {
//     rgblight_sethsv_range(200, 200, 255, 0, 6);
//   } else {
//     rgblight_sethsv_range(200, 200, 0, 0, 6);
//   }
// }

void process_combo_event(uint8_t combo_index, bool pressed) {
  if (!pressed) {
    process_combomap(combo_index);
  }
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  static uint16_t mem_keycode;
  uint16_t prev_keycode = mem_keycode;
  bool is_tapped = ((!record->event.pressed) && (keycode == prev_keycode));
  mem_keycode = keycode;

  switch (keycode) {
    case ZH_RAIS:
      if (record->event.pressed) {
        layer_on(_RAISE);
      } else {
        layer_off(_RAISE);
        if (is_tapped) {
          tap_code(JP_ZHTG);
        }
      }
      return false;
      break;
    case SP_RAIS:
      if (record->event.pressed) {
        layer_on(_RAISE);
      } else {
        layer_off(_RAISE);
        if (is_tapped) {
          tap_code(KC_SPC);
        }
      }
      return false;
      break;

    // case QWERTY:
    //   if (record->event.pressed) {
    //     persistent_default_layer_set(1UL<<_QWERTY);
    //   }
    //   return false;
    //   break;
    // case EISU:
    //   if (record->event.pressed) {
    //     // 薙刀式
    //     // iolite_off();
    //     // 薙刀式
    //     // update_led();
    //   }
    //   return false;
    //   break;
    // case KANA2:
    //   if (record->event.pressed) {
    //     // 薙刀式
    //     // iolite_on();
    //     // 薙刀式
    //     // update_led();
    //   }
    //   return false;
    //   break;
    // case ADJUST:
    //   if (record->event.pressed) {
    //     layer_on(_ADJUST);
    //   } else {
    //     layer_off(_ADJUST);
    //   }
    //   return false;
    //   break;
    // case RAISE:
    //   if (record->event.pressed) {
    //     layer_on(_RAISE);
    //   } else {
    //     layer_off(_RAISE);
    //   }
    //   update_tri_layer(_LOWER, _RAISE, _ADJUST);
    //   // update_led();
    //   return false;
    //   break;
  }

  return true;
}
