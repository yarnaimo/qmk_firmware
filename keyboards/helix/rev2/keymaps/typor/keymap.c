#include QMK_KEYBOARD_H
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
#include "keymap_jp.h"
#include <sendstring_jis.h>

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
    _QWERTY = 0,
    _LOWER,
    _RAISE,
    _FUNC,
    _ADJUST
};

enum custom_keycodes {
  QWERTY = SAFE_RANGE,
  LOWER,
  RAISE,
  FUNC,
  ADJUST,
  EISU,
  KANA,
  KC_C_CV,
  KC_AN,
  KC_IN,
  KC_UN,
  KC_EN,
  KC_ON,
  KC_ATT,
  KC_ITT,
  KC_UTT,
  KC_ETT,
  KC_OTT,
  KC_AH,
  KC_IH,
  KC_UH,
  KC_EH,
  KC_OH,
};


#define KC_ KC_TRNS
#define KC_RESET RESET

#define KC_OSCT OSM(MOD_LCTL)
#define KC_OSSF OSM(MOD_LSFT)

#define KC_C_PD CTL_T(KC_PGDN)
#define KC_C_DN CTL_T(KC_DOWN)
#define KC_A_5 ALT_T(KC_5)
#define KC_A_6 ALT_T(KC_6)
#define KC_S_SP SFT_T(KC_SPC)
#define KC_S_BS SFT_T(KC_BSPC)
#define KC_G_2 GUI_T(KC_2)
#define KC_L_ZH LT(_LOWER, JP_ZHTG) // act as LOWER when hold, as KC_LANG2(=English) when tapped
#define KC_R_KN LT(_RAISE, JP_KANA) // act as RAISE when hold, as KC_LANG1(=Japanese) when tapped

#define KC_C_Z LCTL(KC_Z)
#define KC_C_X LCTL(KC_X)
#define KC_C_C LCTL(KC_C)
#define KC_C_V LCTL(KC_V)
#define KC_CS_Z LCTL(LSFT(KC_Z))

#define KC_WIN AG_SWAP
#define KC_MAC AG_NORM


#define KC_JZHT JP_ZHTG  // hankaku/zenkaku|kanzi
// #define KC_JYEN JP_YEN  // yen, |
#define KC_JCIR JP_CIRC  // ^, ~
#define KC_JAT JP_AT   // @, `
#define KC_JLBR JP_LBRC // [, {
#define KC_JCOL JP_COLN // :, *
#define KC_JRBR JP_RBRC // ], }
#define KC_JBSL JP_BSLS // \, _
#define KC_JMHE JP_MHEN // muhenkan
#define KC_JHEN JP_HENK // henkan
#define KC_JKAN JP_KANA // katakana/hiragana|ro-mazi

#define KC_JMKAN JP_MKANA //kana on MacOSX
#define KC_JMEIS JP_MEISU //eisu on MacOSX

//Aliases for shifted symbols
#define KC_JDQT JP_DQT     // "
#define KC_JAMP JP_AMPR    // &
#define KC_JQUO JP_QUOT    // '
#define KC_JLPR JP_LPRN    // (
#define KC_JRPR JP_RPRN    // )
#define KC_JEQL JP_EQL  // =
#define KC_JTIL JP_TILD // ~
#define KC_JPIP JP_PIPE  // |
#define KC_JGRV JP_GRV    // `
#define KC_JLCB JP_LCBR // {
#define KC_JPLU JP_PLUS // +
#define KC_JAST JP_ASTR // *
#define KC_JRCB JP_RCBR // }
#define KC_JUND JP_UNDS // _


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  [_QWERTY] = LAYOUT_kc(
  //,----+----+----+----+----+----.           ,----+----+----+----+----+----.
     ESC ,SLSH,COMM,JLPR,JRPR,C_CV,            C_Z ,SCLN,JCOL,DOT ,JBSL,DEL ,
  //|----*----*----+----+----+----|           |----+----+----+----*----*----|
      Q  ,MINS,JEQL, C  , X  ,TAB ,            ENT , F  , Z  , K  , B  , P  ,
  //|----*----*----******----+----|           |----+----******----*----*----|
      A  , O  , E  , I  , U  ,PGUP,            UP  , N  , T  , S  , R  , D  ,
  //|----+----+----******----+----+----. ,----+----+----******----+----+----|
      V  , L  , J  , Y  ,HOME,C_PD,END ,  LEFT,C_DN,RGHT, M  , G  , H  , W  ,
  //|----+----+----+----+----+----+----| |----+----+----+----+----+----+----|
      1  ,G_2 , 3  , 4  ,A_5 ,S_SP,JZHT,  JKAN,BSPC,A_6 , 7  , 8  , 9  , 0  \
  //`----+----+----+----+----+----+----/ \----+----+----+----+----+----+----'
  ),

  [_LOWER] = LAYOUT_kc(
  //,----+----+----+----+----+----.           ,----+----+----+----+----+----.
     F1  ,F2  ,F3  ,F4  ,JCIR,PSCR,                ,    ,    ,    ,    ,    ,
  //|----+----+----+----+----+----|           |----+----+----+----+----+----|
     F5  ,F6  ,F7  ,F8  ,JLCB,JRCB,                ,    ,    ,    ,    ,    ,
  //|----+----+----+----+----+----|           |----+----+----+----+----+----|
     F9  ,F10 ,F11 ,F12 ,JLBR,JRBR,                ,    ,    ,    ,    ,    ,
  //|----+----+----+----+----+----+----. ,----+----+----+----+----+----+----|
         ,JPIP,C_C ,C_X ,C_V ,    ,JAT , RESET,    ,    ,    ,    ,    ,    ,
  //|----+----+----+----+----+----+----| |----+----+----+----+----+----+----|
     MUTE,    ,    ,    ,    ,    ,NO  ,  MAC ,    ,    ,    ,    ,    ,    \
  //`----+----+----+----+----+----+----/ \----+----+----+----+----+----+----'
  ),

  [_RAISE] = LAYOUT_kc(
  //,----+----+----+----+----+----.           ,----+----+----+----+----+----.
         ,    ,    ,    ,    ,    ,            INS ,NLCK,PSLS,PAST,PMNS,    ,
  //|----+----+----+----+----+----|           |----+----+----+----+----+----|
     AN  ,ON  ,EN  ,IN  ,UN  ,    ,            JGRV,P7  ,P8  ,P9  ,PPLS,    ,
  //|----+----+----+----+----+----|           |----+----+----+----+----+----|
     ATT ,OTT ,ETT ,ITT ,UTT ,    ,            JTIL,P4  ,P5  ,P6  ,PPLS,    ,
  //|----+----+----+----+----+----+----. ,----+----+----+----+----+----+----|
     AH  ,OH  ,EH  ,IH  ,UH  ,    ,    ,  PAUS,P0  ,P1  ,P2  ,P3  ,PENT,    ,
  //|----+----+----+----+----+----+----| |----+----+----+----+----+----+----|
         ,    ,    ,    ,    ,    ,WIN ,  NO  ,    ,P0  ,    ,PDOT,PENT,    \
  //`----+----+----+----+----+----+----/ \----+----+----+----+----+----+----'
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

// Setting ADJUST layer RGB back to default
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
  static uint16_t mem_keycode;
  uint16_t prev_keycode = mem_keycode;
  bool is_tapped = ((!record->event.pressed) && (keycode == prev_keycode));
  mem_keycode = keycode;

  switch (keycode) {
    case KC_AN: if (record->event.pressed) { SEND_STRING("ann"); } break;
    case KC_IN: if (record->event.pressed) { SEND_STRING("inn"); } break;
    case KC_UN: if (record->event.pressed) { SEND_STRING("unn"); } break;
    case KC_EN: if (record->event.pressed) { SEND_STRING("enn"); } break;
    case KC_ON: if (record->event.pressed) { SEND_STRING("onn"); } break;

    case KC_ATT: if (record->event.pressed) { SEND_STRING("altu"); } break;
    case KC_ITT: if (record->event.pressed) { SEND_STRING("iltu"); } break;
    case KC_UTT: if (record->event.pressed) { SEND_STRING("ultu"); } break;
    case KC_ETT: if (record->event.pressed) { SEND_STRING("eltu"); } break;
    case KC_OTT: if (record->event.pressed) { SEND_STRING("oltu"); } break;

    case KC_AH: if (record->event.pressed) { SEND_STRING("a`"); } break;
    case KC_IH: if (record->event.pressed) { SEND_STRING("i`"); } break;
    case KC_UH: if (record->event.pressed) { SEND_STRING("u`"); } break;
    case KC_EH: if (record->event.pressed) { SEND_STRING("e`"); } break;
    case KC_OH: if (record->event.pressed) { SEND_STRING("o`"); } break;

    case KC_C_CV:
      if (record->event.pressed) {
        tap_code16(KC_C_C);
      } else {
        tap_code16(KC_C_V);
      }
      break;

    case KC_JZHT:
      if (record->event.pressed) {
        layer_on(_LOWER);
      } else {
        layer_off(_LOWER);
        if (is_tapped) {
          tap_code(keycode);
        }
      }
      return false;
      break;
    case KC_JKAN:
      if (record->event.pressed) {
        layer_on(_RAISE);
      } else {
        layer_off(_RAISE);
        if (is_tapped) {
          tap_code(keycode);
        }
      }
      return false;
      break;

    case QWERTY:
      if (record->event.pressed) {
        #ifdef AUDIO_ENABLE
          PLAY_SONG(tone_qwerty);
        #endif
        persistent_default_layer_set(1UL<<_QWERTY);
      }
      return false;
      break;
    case LOWER:
      if (record->event.pressed) {
          //not sure how to have keyboard check mode and set it to a variable, so my work around
          //uses another variable that would be set to true after the first time a reactive key is pressed.
        if (TOG_STATUS) { //TOG_STATUS checks is another reactive key currently pressed, only changes RGB mode if returns false
        } else {
          TOG_STATUS = !TOG_STATUS;
          #ifdef RGBLIGHT_ENABLE
            //rgblight_mode(RGBLIGHT_MODE_SNAKE + 1);
          #endif
        }
        layer_on(_LOWER);
        update_tri_layer_RGB(_LOWER, _RAISE, _ADJUST);
      } else {
        #ifdef RGBLIGHT_ENABLE
          //rgblight_mode(RGB_current_mode);   // revert RGB to initial mode prior to RGB mode change
        #endif
        TOG_STATUS = false;
        layer_off(_LOWER);
        update_tri_layer_RGB(_LOWER, _RAISE, _ADJUST);
      }
      return false;
      break;
    case RAISE:
      if (record->event.pressed) {
        //not sure how to have keyboard check mode and set it to a variable, so my work around
        //uses another variable that would be set to true after the first time a reactive key is pressed.
        if (TOG_STATUS) { //TOG_STATUS checks is another reactive key currently pressed, only changes RGB mode if returns false
        } else {
          TOG_STATUS = !TOG_STATUS;
          #ifdef RGBLIGHT_ENABLE
            //rgblight_mode(RGBLIGHT_MODE_SNAKE);
          #endif
        }
        layer_on(_RAISE);
        update_tri_layer_RGB(_LOWER, _RAISE, _ADJUST);
      } else {
        #ifdef RGBLIGHT_ENABLE
          //rgblight_mode(RGB_current_mode);  // revert RGB to initial mode prior to RGB mode change
        #endif
        layer_off(_RAISE);
        TOG_STATUS = false;
        update_tri_layer_RGB(_LOWER, _RAISE, _ADJUST);
      }
      return false;
      break;
    case FUNC:
      if (record->event.pressed) {
          layer_on(_FUNC);
        } else {
          layer_off(_FUNC);
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
#define L_LOWER (1<<_LOWER)
#define L_RAISE (1<<_RAISE)
#define L_FUNC (1<<_FUNC)
#define L_ADJUST (1<<_ADJUST)
#define L_ADJUST_TRI (L_ADJUST|L_RAISE|L_LOWER)

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
        case L_RAISE:
           matrix_write_P(matrix, PSTR("Raise"));
           break;
        case L_LOWER:
           matrix_write_P(matrix, PSTR("Lower"));
           break;
        case L_FUNC:
            matrix_write_P(matrix, PSTR("Func"));
            break;
        case L_ADJUST:
        case L_ADJUST_TRI:
           matrix_write_P(matrix, PSTR("Adjust"));
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
