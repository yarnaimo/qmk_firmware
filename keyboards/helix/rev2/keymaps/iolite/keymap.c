/* Copyright 2018-2019 eswai <@eswai>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include QMK_KEYBOARD_H
#include "bootloader.h"
#ifdef PROTOCOL_LUFA
  #include "lufa.h"
  #include "split_util.h"
#endif
#ifdef SSD1306OLED
  #include "ssd1306.h"
#endif

#include "keymap_jp.h"

// 薙刀式
#include "iolite.h"
ILKEYS iolite_keys;
// 薙刀式

void update_led(void);

extern keymap_config_t keymap_config;

#ifdef RGBLIGHT_ENABLE
//Following line allows macro to read current RGB settings
extern rgblight_config_t rgblight_config;
#endif

extern uint8_t is_master;

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
enum keymap_layers {
  _QWERTY,
  _EUCALYN,
  _WORKMAN,
// 薙刀式
  _IOLITE, // 薙刀式入力レイヤー
// 薙刀式
  _LOWER,
  _RAISE,
  _ADJUST,
};

// 薙刀式
enum combo_events {
  IOLITE_ON_CMB,
  IOLITE_OFF_CMB,
};

#if defined(DQWERTY)
const uint16_t PROGMEM ngon_combo[] = {KC_H, KC_J, COMBO_END};
const uint16_t PROGMEM ngoff_combo[] = {KC_F, KC_G, COMBO_END};
#endif
#if defined(DEUCALYN)
const uint16_t PROGMEM ngon_combo[] = {KC_G, KC_T, COMBO_END};
const uint16_t PROGMEM ngoff_combo[] = {KC_I, KC_U, COMBO_END};
#endif
#if defined(DWORKMAN)
const uint16_t PROGMEM ngon_combo[] = {KC_Y, KC_N, COMBO_END};
const uint16_t PROGMEM ngoff_combo[] = {KC_T, KC_G, COMBO_END};
#endif

combo_t key_combos[COMBO_COUNT] = {
  [IOLITE_ON_CMB] = COMBO_ACTION(ngon_combo),
  [IOLITE_OFF_CMB] = COMBO_ACTION(ngoff_combo),
};

// IME ONのcombo
void process_combo_event(uint8_t combo_index, bool pressed) {
  switch(combo_index) {
    case IOLITE_ON_CMB:
      if (pressed) {
        iolite_on();
        update_led();
      }
      break;
    case IOLITE_OFF_CMB:
      if (pressed) {
        iolite_off();
        update_led();
      }
      break;
  }
}
// 薙刀式

enum custom_keycodes {
  QWERTY = IL_SAFE_RANGE,
  EUCALYN,
  WORKMAN,
  EISU,
  LOWER,
  RAISE,
  ADJUST,
  BACKLIT,
  KANA2,
  UNDGL,
  RGBRST
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
#define CS_Z LCTL(LSFT(KC_Z))

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_IOLITE] = LAYOUT(
    KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                      KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_DEL,  \
    KC_TAB,  IL_Q,    IL_W,    IL_E,    IL_R,    IL_T,                      IL_Y,    IL_U,    IL_I,    IL_O,    IL_P,    KC_BSPC, \
    KC_LALT, IL_A,    IL_S,    IL_D,    IL_F,    IL_G,                      IL_H,    IL_J,    IL_K,    IL_L,    IL_SCLN, KC_ENT,  \
    KC_LSFT, IL_Z,    IL_X,    IL_C,    IL_V,    IL_B,    C_C,     C_Z,     IL_N,    IL_M,    IL_COMM, IL_DOT,  IL_SLSH, KC_MINS, \
    KC_LCTL, KC_LGUI, IL_PGDN, IL_END,  IL_TMB1, IL_TMB2, IL_TMB3, IL_TMB4, IL_TMB5, IL_TMB6, IL_LEFT, IL_UP,   IL_DOWN, IL_RGHT  \
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

void matrix_init_user(void) {
  // 薙刀式
  set_iolite(_IOLITE);
  #ifdef IOLITE_EDIT_MAC
  set_unicode_input_mode(UC_OSX);
  #endif
  #ifdef IOLITE_EDIT_WIN
  set_unicode_input_mode(UC_WINC);
  #endif
  // 薙刀式

  #ifdef RGBLIGHT_ENABLE
    RGB_current_mode = rgblight_config.mode;
  #endif
  //SSD1306 OLED init, make sure to add #define SSD1306OLED in config.h
  #ifdef SSD1306OLED
      iota_gfx_init(!has_usb());   // turns on the display
  #endif
}

//SSD1306 OLED update loop, make sure to add #define SSD1306OLED in config.h
#ifdef SSD1306OLED

// When add source files to SRC in rules.mk, you can use functions.
const char *read_layer_state(void);
const char *read_logo(void);
void set_keylog(uint16_t keycode, keyrecord_t *record);
const char *read_keylog(void);
const char *read_keylogs(void);

// const char *read_mode_icon(bool swap);
// const char *read_host_led_state(void);
// void set_timelog(void);
// const char *read_timelog(void);

void matrix_scan_user(void) {
   iota_gfx_task();
}

void matrix_render_user(struct CharacterMatrix *matrix) {
  if (is_master) {
    // If you want to change the display of OLED, you need to change here
    matrix_write_ln(matrix, read_layer_state());
    matrix_write_ln(matrix, read_keylog());
    matrix_write_ln(matrix, read_keylogs());
    //matrix_write_ln(matrix, read_mode_icon(keymap_config.swap_lalt_lgui));
    //matrix_write_ln(matrix, read_host_led_state());
    //matrix_write_ln(matrix, read_timelog());
  } else {
    matrix_write(matrix, read_logo());
  }
}

void matrix_update(struct CharacterMatrix *dest, const struct CharacterMatrix *source) {
  if (memcmp(dest->display, source->display, sizeof(dest->display))) {
    memcpy(dest->display, source->display, sizeof(dest->display));
    dest->dirty = true;
  }
}

void iota_gfx_task_user(void) {
  struct CharacterMatrix matrix;
  matrix_clear(&matrix);
  matrix_render_user(&matrix);
  matrix_update(&display, &matrix);
}
#endif//SSD1306OLED

static bool underglow = false;

void update_led() {
  if (layer_state_is(_LOWER) && !isLeftHand) {
    // rgblight_setrgb_at(0, 0, 200, 7);
    rgblight_sethsv_at(200, 100, 255, 15);
    rgblight_sethsv_at(200, 100, 255, 16);
    rgblight_sethsv_at(200, 100, 255, 17);
    rgblight_sethsv_at(200, 100, 255, 18);
    rgblight_sethsv_at(200, 100, 255, 19);
    rgblight_sethsv_at(200, 100, 255, 20);
    rgblight_sethsv_at(200, 100, 255, 21);
    rgblight_sethsv_at(200, 100, 255, 22);
    rgblight_sethsv_at(200, 100, 255, 23);
  }
  if (layer_state_is(_RAISE) && !isLeftHand) {
    rgblight_sethsv_at(200, 100, 255, 11);
    rgblight_sethsv_at(200, 100, 255, 16);
    rgblight_sethsv_at(200, 100, 255, 17);
    rgblight_sethsv_at(200, 100, 255, 19);
  }
  if (!layer_state_is(_LOWER) && !layer_state_is(_RAISE)) {
    rgblight_sethsv_range(0, 0, 0, 6, 27);
  }
  if (iolite_state()) {
    rgblight_sethsv_at(200, 200, 255, 6);
    rgblight_sethsv_at(200, 200, 255, 13);
    rgblight_sethsv_at(200, 200, 255, 14);
  } else {
    rgblight_sethsv_at(0, 0, 0, 6);
    rgblight_sethsv_at(0, 0, 0, 13);
    rgblight_sethsv_at(0, 0, 0, 14);
  }
  if (underglow) {
    rgblight_sethsv_range(200, 200, 255, 0, 6);
  } else {
    rgblight_sethsv_range(200, 200, 0, 0, 6);
  }
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  if (record->event.pressed) {
#ifdef SSD1306OLED
    set_keylog(keycode, record);
#endif
    // set_timelog();
  }

  switch (keycode) {
    case UNDGL:
      if (record->event.pressed) {
        underglow = !underglow;
      }
      update_led();
      return false;
      break;
    case QWERTY:
      if (record->event.pressed) {
        persistent_default_layer_set(1UL<<_QWERTY);
      }
      return false;
      break;
    case EUCALYN:
      if (record->event.pressed) {
        persistent_default_layer_set(1UL<<_EUCALYN);
      }
      return false;
      break;
    case WORKMAN:
      if (record->event.pressed) {
        persistent_default_layer_set(1UL<<_WORKMAN);
      }
      return false;
      break;
    case EISU:
      if (record->event.pressed) {
        // 薙刀式
        iolite_off();
        // 薙刀式
        update_led();
      }
      return false;
      break;
    case KANA2:
      if (record->event.pressed) {
        // 薙刀式
        iolite_on();
        // 薙刀式
        update_led();
      }
      return false;
      break;
    case ADJUST:
      if (record->event.pressed) {
        layer_on(_ADJUST);
      } else {
        layer_off(_ADJUST);
      }
      return false;
      break;
    case RGB_MOD:
      #ifdef RGBLIGHT_ENABLE
        if (record->event.pressed) {
          rgblight_mode(RGB_current_mode);
          rgblight_step();
          RGB_current_mode = rgblight_config.mode;
        }
      #endif
      return false;
      break;
    case RGBRST:
      #ifdef RGBLIGHT_ENABLE
        if (record->event.pressed) {
          eeconfig_update_rgblight_default();
          rgblight_enable();
          RGB_current_mode = rgblight_config.mode;
        }
      #endif
      return false;
      break;
    case LOWER:
      if (record->event.pressed) {
        layer_on(_LOWER);
      } else {
        layer_off(_LOWER);
      }
      update_tri_layer(_LOWER, _RAISE, _ADJUST);
      update_led();
      return false;
      break;
    case RAISE:
      if (record->event.pressed) {
        layer_on(_RAISE);
      } else {
        layer_off(_RAISE);
      }
      update_tri_layer(_LOWER, _RAISE, _ADJUST);
      update_led();
      return false;
      break;
  }

  // 薙刀式
  bool a = true;
  if (iolite_state()) {
    iolite_mode(keycode, record);
    a = process_iolite(keycode, record);
    // update_led();
  }
  if (a == false) return false;
  // 薙刀式

  return true;
}