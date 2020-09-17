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
  _IOLITE,
  _SYMBOL_L,
  _SYMBOL_R,
  _SYMBOL_LR,
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
#define S_CAPS SFT_T(KC_CAPS)
#define A_ZHTG ALT_T(JP_ZHTG)

#define IL_COMM SFT_T(KC_COMM)
#define IL_DOT SFT_T(KC_DOT)

#define KMINS_L LT(_SYMBOL_L, KC_MINS)
#define JEQL_R LT(_SYMBOL_R, JP_EQL)
#define JCOLN_LR LT(_SYMBOL_LR, JP_COLN)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_IOLITE] = LAYOUT(
    KC_ESC , KC_1   , KC_2   , KC_3   , KC_4   , KC_5   ,                   KC_6   , KC_7   , KC_8   , KC_9   , KC_0   , KC_DEL , \
    KC_TAB , KC_J   , KC_E   , KC_A   , KC_Y   , JP_EQL ,                   KC_F   , KC_G   , KC_K   , KC_R   , KC_P   , KC_BSPC, \
    A_ZHTG , KC_C   , KC_O   , KC_U   , KC_I   , KC_MINS,                   KC_H   , KC_T   , KC_S   , KC_N   , KC_D   , KC_ENT , \
    KC_LSFT, JP_COLN, KC_Q   , KC_X   , KC_W   , KC_V   , C_C    , C_Z    , KC_B   , KC_M   , KC_Z   , KC_L   , KC_UP  , JP_SCLN,  \
    KC_LCTL, KC_LGUI, S_CAPS , KC_CAPS, JP_MHEN, KC_COMM, SP_RAIS, SP_RAIS, KC_DOT , KC_SLSH, JP_HENK, KC_LEFT, KC_DOWN, KC_RGHT  \
  ),

  [_SYMBOL_L] = LAYOUT(
    _______, _______, _______, _______, _______, _______,                   _______, _______, JP_AT  , JP_ASTR, JP_CIRC, _______, \
    _______, _______, _______, _______, _______, _______,                   JP_GRV , JP_QUOT, JP_LBRC, JP_DQT , JP_PLUS, _______, \
    _______, _______, _______, _______, _______, _______,                   JP_SLSH, JP_LPRN, JP_LT  , JP_LCBR, JP_QUES, _______, \
    _______, _______, _______, _______, _______, _______, _______, _______, JP_TILD, JP_UNDS, JP_PIPE, JP_BSLS, _______, _______, \
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______  \
  ),

  [_SYMBOL_R] = LAYOUT(
    _______, _______, _______, _______, _______, _______,                   _______, _______, _______, _______, _______, _______, \
    _______, _______, _______, _______, _______, _______,                   _______, _______, JP_RBRC, _______, _______, _______, \
    _______, _______, _______, _______, _______, _______,                   _______, JP_RPRN, JP_GT  , JP_RCBR, _______, _______, \
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, \
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______  \
  ),

  [_SYMBOL_LR] = LAYOUT(
    _______, _______, _______, _______, _______, _______,                   _______, _______, _______, _______, _______, _______, \
    _______, _______, _______, _______, _______, _______,                   _______, _______, LR_BRC , _______, _______, _______, \
    _______, _______, _______, _______, _______, _______,                   _______, LR_PRN , LR_T   , LR_CBR , _______, _______, \
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, \
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______  \
  ),

  [_RAISE] = LAYOUT(
    _______, KC_F1  , KC_F2  , KC_F3  , KC_F4  , KC_F5  ,                   KC_PSCR, KC_NLCK, KC_PSLS, KC_PAST, KC_PMNS, _______, \
    _______, KC_F6  , KC_F7  , KC_F8  , KC_F9  , KC_F10 ,                   KC_MUTE, KC_P7  , KC_P8  , KC_P9  , KC_PPLS, _______, \
    _______, KC_F11 , KC_F12 , JP_BSLS, CS_I   , C_SLSH ,                   KC_PAUS, KC_P4  , KC_P5  , KC_P6  , KC_PENT, _______, \
    _______, JP_CIRC, JP_AT  , JP_LBRC, JP_RBRC, C_X    , C_V    , CS_Z   , KC_INS , KC_P1  , KC_P2  , KC_P3  , KC_PDOT, _______, \
    _______, _______, JP_PIPE, RESET  , AG_SWAP, AG_NORM, _______, _______, KC_P0  , KC_P0  , _______, _______, _______, _______  \
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

  void st(uint16_t kc) {
    if (record->event.pressed) {
      SEND_STRING(SS_DOWN(X_LSHIFT));
    } else {
      SEND_STRING(SS_UP(X_LSHIFT));
      if (is_tapped) {
        tap_code(kc);
      }
    }
  }

  void lt(uint16_t kc, uint8_t layer) {
    if (record->event.pressed) {
      layer_on(layer);
    } else {
      layer_off(layer);
      if (is_tapped) {
        tap_code(kc);
      }
    }
  }

  switch (keycode) {
    // case ZH_RAIS:
    //   lt(JP_ZHTG, _RAISE);
    //   return false;
    //   break;

    case KC_COMM:
      st(KC_COMM);
      return false;

    case KC_DOT:
      st(KC_DOT);
      return false;

    case KC_MINS:
      lt(KC_MINS, _SYMBOL_L);
      return false;

    case JP_EQL:
      lt(JP_EQL, _SYMBOL_R);
      return false;

    case JP_COLN:
      lt(JP_COLN, _SYMBOL_LR);
      return false;

    case SP_RAIS:
      lt(KC_SPC, _RAISE);
      return false;

    case LR_BRC:
      if (record->event.pressed) {
        SEND_STRING("[]" SS_TAP(X_LEFT));
      }
      return false;

    case LR_PRN:
      if (record->event.pressed) {
        SEND_STRING("()" SS_TAP(X_LEFT));
      }
      return false;

    case LR_T:
      if (record->event.pressed) {
        SEND_STRING("<>" SS_TAP(X_LEFT));
      }
      return false;

    case LR_CBR:
      if (record->event.pressed) {
        SEND_STRING("{}" SS_TAP(X_LEFT));
      }
      return false;

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
