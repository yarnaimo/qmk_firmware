#include QMK_KEYBOARD_H
#include "keymap_jp.h"
#include "bootloader.h"
#ifdef PROTOCOL_LUFA
#include "lufa.h"
#include "split_util.h"
#endif
#ifdef AUDIO_ENABLE
  #include "audio.h"
#endif
#ifdef SSD1306OLED
  #include "ssd1306.h"
#endif

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
enum layer_number {
    _KINU = 0,
    _LAYER1,
    _LAYER2
};

enum custom_keycodes {
  KINU = SAFE_RANGE,
  LAYER1,
  LAYER2,
  BACKLIT,
  EISU,
  KANA,
  RGBRST
};

enum macro_keycodes {
  KC_SAMPLEMACRO,
};


// Fillers to make layering more clear
#define _______ KC_TRNS
#define XXXXXXX KC_NO
//Macros
#define M_SAMPLE M(KC_SAMPLEMACRO)

#define SFT_SP SFT_T(KC_SPC)

#define ZHTG_L2 LT(_LAYER2, JP_ZHTG)
#define KANA_L2 LT(_LAYER2, JP_KANA)
#define SPC_L1 LT(_LAYER1, KC_SPC)
#define ZHTG_L1 LT(_LAYER1, JP_ZHTG)

#define OSM_SFT MT(MOD_LSFT, OSM(MOD_LSFT))

#define OSL_L2 OSL(_LAYER2)

#define ALT_ZH ALT_T(JP_ZHTG)
#define ALT_KA ALT_T(JP_KANA)

#define PRV_TAB LCTL(LSFT(KC_TAB))
#define NXT_TAB LCTL(KC_TAB)
#define PREV LALT(KC_LEFT)
#define NEXT LALT(KC_RGHT)

#define CTL_A LCTL(KC_A)
#define CTL_Z LCTL(KC_Z)
#define CTL_X LCTL(KC_X)
#define CTL_C LCTL(KC_C)
#define CTL_V LCTL(KC_V)
#define CTL_F LCTL(KC_F)
#define CTL_T_ LCTL(KC_T)
#define CTL_W LCTL(KC_W)
#define CTL_S LCTL(KC_S)

// pnl nlp
// RN RK RS RT RM RG DR FR TS REI SK MK CK
// OI OE OU OA AI AU EA EU EI GHT MB CL BY LD RD RL shadow

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  [_KINU] = LAYOUT( \
      KC_ESC , CTL_X  , CTL_C  , CTL_V  , CTL_F  , KC_MUTE,                   JP_AT  , JP_CIRC, JP_COLN, JP_QUOT, JP_HASH, KC_DEL , \
      KC_TAB , KC_Q   , KC_F   , KC_E   , KC_Z   , JP_LPRN,                   JP_SLSH, KC_L   , KC_K   , KC_B   , KC_W   , KC_BSPC, \
      KC_LALT, KC_A   , KC_U   , KC_O   , KC_I   , KC_P   ,                   KC_N   , KC_S   , KC_T   , KC_R   , KC_Y   , KC_ENT , \
      JP_LBRC, KC_V   , JP_DOT , KC_J   , KC_D   , KC_X   , CTL_Z  , KC_PSCR, KC_H   , KC_M   , KC_G   , JP_COMM, KC_C   , JP_MINS, \
      KC_LCTL, KC_LGUI, CTL_S  , KC_LCTL, SPC_L1 , LAYER2 , OSM_SFT, ZHTG_L1, KC_SPC , LAYER2 , KC_RALT, XXXXXXX, KC_APP , KC_RCTL  \
      ),

  // [_KINU] = LAYOUT( 
  //     KC_ESC , KC_Z   , KC_V   , KC_H   , KC_F   , FIND   ,                   JP_AT  , JP_EXLM, JP_COLN, JP_QUOT, JP_HASH, KC_DEL , 
  //     KC_TAB , KC_W   , KC_E   , KC_N   , KC_P   , JP_LBRC,                   JP_SLSH, KC_M   , KC_O   , KC_U   , KC_J   , KC_BSPC, 
  //     KC_LCTL, KC_S   , KC_C   , KC_K   , KC_T   , JP_LPRN,                   JP_MINS, KC_G   , KC_I   , KC_R   , KC_A   , KC_ENT , 
  //     OSL_L2 , UNDO   , CUT    , COPY   , PSTE   , KC_D   , KC_MUTE, KC_PSCR, KC_L   , KC_Y   , KC_X   , KC_Q   , KC_B   , KC_INS , 
  //     LAYER1 , KC_LGUI, ALL    , KC_LALT, JP_COMM, SFT_SP , _LAYER2, JP_ZHTG, SFT_SP , JP_DOT , KC_RALT, XXXXXXX, KC_APP , LAYER1   
  //     ),

  [_LAYER1] =  LAYOUT( \
      KC_F1  , KC_F2  , KC_F3  , KC_F4  , KC_F5  , KC_F6  ,                   XXXXXXX, XXXXXXX, JP_SCLN, JP_DQT , XXXXXXX, _______, \
      KC_F7  , KC_F8  , KC_F9  , KC_F10 , KC_F11 , KC_F12 ,                   JP_PERC, JP_PLUS, KC_UP  , JP_EXLM, JP_DLR , _______, \
      KC_P1  , KC_P2  , KC_P3  , KC_P4  , KC_P5  , KC_P6  ,                   JP_AMPR, KC_LEFT, KC_DOWN, KC_RGHT, JP_BSLS, _______, \
      KC_P7  , KC_P8  , KC_P9  , KC_P0  , XXXXXXX, XXXXXXX, XXXXXXX, KC_INS , XXXXXXX, JP_UNDS, XXXXXXX, JP_PIPE, XXXXXXX, _______, \
      _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______  \
      ),

  [_LAYER2] =  LAYOUT( \
      _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                   KC_PAUS, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______, \
      _______, XXXXXXX, CTL_W  , KC_PGUP, CTL_T_ , JP_RPRN,                   XXXXXXX, KC_P1  , KC_P2  , KC_P3  , XXXXXXX, _______, \
      _______, PRV_TAB, KC_HOME, KC_PGDN, KC_END , NXT_TAB,                   XXXXXXX, KC_P4  , KC_P5  , KC_P6  , XXXXXXX, _______, \
      JP_RBRC, XXXXXXX, PREV   , XXXXXXX, NEXT   , XXXXXXX, AG_NORM, AG_SWAP, XXXXXXX, KC_P7  , KC_P8  , KC_P9  , XXXXXXX, _______, \
      _______, _______, _______, _______, _______, _______, _______, JP_HENK, _______, KC_P0  , KC_P0  , _______, _______, _______  \
      )
};


#ifdef AUDIO_ENABLE

float tone_qwerty[][2]     = SONG(QWERTY_SOUND);
float tone_dvorak[][2]     = SONG(DVORAK_SOUND);
float tone_colemak[][2]    = SONG(COLEMAK_SOUND);
float tone_plover[][2]     = SONG(PLOVER_SOUND);
float tone_plover_gb[][2]  = SONG(PLOVER_GOODBYE_SOUND);
float music_scale[][2]     = SONG(MUSIC_SCALE_SOUND);
#endif

// define variables for reactive RGB
bool TOG_STATUS = false;
int RGB_current_mode;

void persistent_default_layer_set(uint16_t default_layer) {
  eeconfig_update_default_layer(default_layer);
  default_layer_set(default_layer);
}

// Setting LAYER1 layer RGB back to default
void update_tri_layer_RGB(uint8_t layer1, uint8_t layer2, uint8_t layer3) {
  if (IS_LAYER_ON(layer1) && IS_LAYER_ON(layer2)) {
    #ifdef RGBLIGHT_ENABLE
      //rgblight_mode(RGB_current_mode);
    #endif
    layer_on(layer3);
  } else {
    layer_off(layer3);
  }
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case KINU:
      if (record->event.pressed) {
        #ifdef AUDIO_ENABLE
          PLAY_SONG(tone_qwerty);
        #endif
        persistent_default_layer_set(1UL<<_KINU);
      }
      return false;
      break;
    case LAYER1:
      if (record->event.pressed) {
        layer_on(_LAYER1);
      } else {
        layer_off(_LAYER1);
      }
      return false;
      break;
    case LAYER2:
      if (record->event.pressed) {
        layer_on(_LAYER2);
      } else {
        layer_off(_LAYER2);
      }
      return false;
      break;
      //led operations - RGB mode change now updates the RGB_current_mode to allow the right RGB mode to be set after reactive keys are released
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
    case EISU:
      if (record->event.pressed) {
        if(keymap_config.swap_lalt_lgui==false){
          register_code(KC_LANG2);
        }else{
          SEND_STRING(SS_LALT("`"));
        }
      } else {
        unregister_code(KC_LANG2);
      }
      return false;
      break;
    case KANA:
      if (record->event.pressed) {
        if(keymap_config.swap_lalt_lgui==false){
          register_code(KC_LANG1);
        }else{
          SEND_STRING(SS_LALT("`"));
        }
      } else {
        unregister_code(KC_LANG1);
      }
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
      break;
  }
  return true;
}

void matrix_init_user(void) {
    #ifdef AUDIO_ENABLE
        startup_user();
    #endif
    #ifdef RGBLIGHT_ENABLE
      RGB_current_mode = rgblight_config.mode;
    #endif
    //SSD1306 OLED init, make sure to add #define SSD1306OLED in config.h
    #ifdef SSD1306OLED
        iota_gfx_init(!has_usb());   // turns on the display
    #endif
}


#ifdef AUDIO_ENABLE

void startup_user()
{
    _delay_ms(20); // gets rid of tick
}

void shutdown_user()
{
    _delay_ms(150);
    stop_all_notes();
}

void music_on_user(void)
{
    music_scale_user();
}

void music_scale_user(void)
{
    PLAY_SONG(music_scale);
}

#endif


//SSD1306 OLED update loop, make sure to add #define SSD1306OLED in config.h
#ifdef SSD1306OLED

// hook point for 'led_test' keymap
//   'default' keymap's led_test_init() is empty function, do nothing
//   'led_test' keymap's led_test_init() force rgblight_mode_noeeprom(RGBLIGHT_MODE_RGB_TEST);
__attribute__ ((weak))
void led_test_init(void) {}

void matrix_scan_user(void) {
     led_test_init();
     iota_gfx_task();  // this is what updates the display continuously
}

void matrix_update(struct CharacterMatrix *dest,
                          const struct CharacterMatrix *source) {
  if (memcmp(dest->display, source->display, sizeof(dest->display))) {
    memcpy(dest->display, source->display, sizeof(dest->display));
    dest->dirty = true;
  }
}

//assign the right code to your layers for OLED display
#define L_BASE 0
#define L_LAYER1 (1<<_LAYER1)
#define L_LAYER2 (1<<_LAYER2)

static void render_logo(struct CharacterMatrix *matrix) {

  static char logo[]={
    0x80,0x81,0x82,0x83,0x84,0x85,0x86,0x87,0x88,0x89,0x8a,0x8b,0x8c,0x8d,0x8e,0x8f,0x90,0x91,0x92,0x93,0x94,
    0xa0,0xa1,0xa2,0xa3,0xa4,0xa5,0xa6,0xa7,0xa8,0xa9,0xaa,0xab,0xac,0xad,0xae,0xaf,0xb0,0xb1,0xb2,0xb3,0xb4,
    0xc0,0xc1,0xc2,0xc3,0xc4,0xc5,0xc6,0xc7,0xc8,0xc9,0xca,0xcb,0xcc,0xcd,0xce,0xcf,0xd0,0xd1,0xd2,0xd3,0xd4,
    0};
  matrix_write(matrix, logo);
  //matrix_write_P(&matrix, PSTR(" Split keyboard kit"));
}



void render_status(struct CharacterMatrix *matrix) {

  // Render to mode icon
  static char logo[][2][3]={{{0x95,0x96,0},{0xb5,0xb6,0}},{{0x97,0x98,0},{0xb7,0xb8,0}}};
  if(keymap_config.swap_lalt_lgui==false){
    matrix_write(matrix, logo[0][0]);
    matrix_write_P(matrix, PSTR("\n"));
    matrix_write(matrix, logo[0][1]);
  }else{
    matrix_write(matrix, logo[1][0]);
    matrix_write_P(matrix, PSTR("\n"));
    matrix_write(matrix, logo[1][1]);
  }

  // Define layers here, Have not worked out how to have text displayed for each layer. Copy down the number you see and add a case for it below
  char buf[40];
  snprintf(buf,sizeof(buf), "Undef-%ld", layer_state);
  matrix_write_P(matrix, PSTR("\nLayer: "));
    switch (layer_state) {
        case L_BASE:
           matrix_write_P(matrix, PSTR("Default"));
           break;
        case L_LAYER1:
           matrix_write_P(matrix, PSTR("Layer1"));
           break;
        case L_LAYER2:
           matrix_write_P(matrix, PSTR("Layer2"));
           break;
        default:
           matrix_write(matrix, buf);
    }

  // Host Keyboard LED Status
  char led[40];
    snprintf(led, sizeof(led), "\n%s  %s  %s",
            (host_keyboard_leds() & (1<<USB_LED_NUM_LOCK)) ? "NUMLOCK" : "       ",
            (host_keyboard_leds() & (1<<USB_LED_CAPS_LOCK)) ? "CAPS" : "    ",
            (host_keyboard_leds() & (1<<USB_LED_SCROLL_LOCK)) ? "SCLK" : "    ");
  matrix_write(matrix, led);
}


void iota_gfx_task_user(void) {
  struct CharacterMatrix matrix;

#if DEBUG_TO_SCREEN
  if (debug_enable) {
    return;
  }
#endif

  matrix_clear(&matrix);
  if(is_master){
    render_status(&matrix);
  }else{
    render_logo(&matrix);
  }
  matrix_update(&display, &matrix);
}

#endif
