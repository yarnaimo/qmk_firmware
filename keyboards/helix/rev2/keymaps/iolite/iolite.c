#include QMK_KEYBOARD_H
#include "keyboards/helix/rev2/rev2.h"
#include "iolite.h"

#if !defined(__AVR__)
  #include <string.h>
  #define memcpy_P(des, src, len) memcpy(des, src, len)
#endif

#define ILBUFFER 5 // バッファのサイズ

static uint8_t ng_chrcount = 0; // 文字キー入力のカウンタ (シフトキーを除く)
static bool is_iolite = false; // 薙刀式がオンかオフか
static uint8_t iolite_layer = 0; // レイヤー番号
static uint8_t n_modifier = 0; // 押しているmodifierキーの数
static uint64_t keycomb = 0UL; // 同時押しの状態を示す。32bitの各ビットがキーに対応する。

// 31キーを32bitの各ビットに割り当てる
#define B_Q    (1UL<<0)
#define B_W    (1UL<<1)
#define B_E    (1UL<<2)
#define B_R    (1UL<<3)
#define B_T    (1UL<<4)

#define B_Y    (1UL<<5)
#define B_U    (1UL<<6)
#define B_I    (1UL<<7)
#define B_O    (1UL<<8)
#define B_P    (1UL<<9)

#define B_A    (1UL<<10)
#define B_S    (1UL<<11)
#define B_D    (1UL<<12)
#define B_F    (1UL<<13)
#define B_G    (1UL<<14)

#define B_H    (1UL<<15)
#define B_J    (1UL<<16)
#define B_K    (1UL<<17)
#define B_L    (1UL<<18)
#define B_SCLN (1UL<<19)

#define B_Z    (1UL<<20)
#define B_X    (1UL<<21)
#define B_C    (1UL<<22)
#define B_V    (1UL<<23)
#define B_B    (1UL<<24)

#define B_N    (1UL<<25)
#define B_M    (1UL<<26)
#define B_COMM (1UL<<27)
#define B_DOT  (1UL<<28)
#define B_SLSH (1UL<<29)

#define B_SHFT (1UL<<30)

#define B_HOME (1UL<<31)
#define B_PGUP (1UL<<32)
#define B_PGDN (1UL<<33)
#define B_END  (1UL<<34)
#define B_TMB1 (1UL<<35)
#define B_TMB2 (1UL<<36)
#define B_TMB3 (1UL<<37)

#define B_TMB4 (1UL<<38)
#define B_TMB5 (1UL<<39)
#define B_TMB6 (1UL<<40)
#define B_LEFT (1UL<<41)
#define B_UP   (1UL<<42)
#define B_DOWN (1UL<<43)
#define B_RGHT (1UL<<44)

// 文字入力バッファ
static uint16_t ninputs[ILBUFFER];

// キーコードとキービットの対応
// メモリ削減のため配列はNG_Qを0にしている
const uint64_t ng_key[] = {
  [IL_Q    - IL_Q] = B_Q,
  [IL_W    - IL_Q] = B_W,
  [IL_E    - IL_Q] = B_E,
  [IL_R    - IL_Q] = B_R,
  [IL_T    - IL_Q] = B_T,

  [IL_Y    - IL_Q] = B_Y,
  [IL_U    - IL_Q] = B_U,
  [IL_I    - IL_Q] = B_I,
  [IL_O    - IL_Q] = B_O,
  [IL_P    - IL_Q] = B_P,

  [IL_A    - IL_Q] = B_A,
  [IL_S    - IL_Q] = B_S,
  [IL_D    - IL_Q] = B_D,
  [IL_F    - IL_Q] = B_F,
  [IL_G    - IL_Q] = B_G,

  [IL_H    - IL_Q] = B_H,
  [IL_J    - IL_Q] = B_J,
  [IL_K    - IL_Q] = B_K,
  [IL_L    - IL_Q] = B_L,
  [IL_SCLN - IL_Q] = B_SCLN,

  [IL_Z    - IL_Q] = B_Z,
  [IL_X    - IL_Q] = B_X,
  [IL_C    - IL_Q] = B_C,
  [IL_V    - IL_Q] = B_V,
  [IL_B    - IL_Q] = B_B,

  [IL_N    - IL_Q] = B_N,
  [IL_M    - IL_Q] = B_M,
  [IL_COMM - IL_Q] = B_COMM,
  [IL_DOT  - IL_Q] = B_DOT,
  [IL_SLSH - IL_Q] = B_SLSH,

  [IL_SHFT - IL_Q] = B_SHFT,

  [IL_HOME - IL_Q] = B_HOME,
  [IL_PGUP - IL_Q] = B_PGUP,
  [IL_PGDN - IL_Q] = B_PGDN,
  [IL_END  - IL_Q] = B_END,
  [IL_TMB1 - IL_Q] = B_TMB1,
  [IL_TMB2 - IL_Q] = B_TMB2,
  [IL_TMB3 - IL_Q] = B_TMB3,

  [IL_TMB4 - IL_Q] = B_TMB4,
  [IL_TMB5 - IL_Q] = B_TMB5,
  [IL_TMB6 - IL_Q] = B_TMB6,
  [IL_LEFT - IL_Q] = B_LEFT,
  [IL_UP   - IL_Q] = B_UP,
  [IL_DOWN - IL_Q] = B_DOWN,
  [IL_RGHT - IL_Q] = B_RGHT,
};

enum symbol_code {
  S_QUOT,
  S_DQT,
  S_GRV,
  S_PRN,
  S_BRC,
  S_CBR,
  S_LGT,

  S_NUM,
};

char sym_left[S_NUM][1] = {
  "'",
  "\"",
  "`",
  "(",
  "[",
  "{",
  "<",
};

char sym_right[S_NUM][1] = {
  "'",
  "\"",
  "`",
  ")",
  "]",
  "}",
  ">",
};

char sym_pair[S_NUM][5] = {
  "''"SS_TAP(X_LEFT),
  "\"\""SS_TAP(X_LEFT),
  "``"SS_TAP(X_LEFT),
  "()"SS_TAP(X_LEFT),
  "[]"SS_TAP(X_LEFT),
  "{}"SS_TAP(X_LEFT),
  "<>"SS_TAP(X_LEFT),
};

// char type_sleft(enum symbol_code code) {
//   return symbol_left[code];
// }

// char type_sright(enum symbol_code code) {
//   return symbol_left[code];
// }

// char type_s(enum symbol_code code) {
//   return "type_sright(code)" SS_TAP(X_LEFT);
// }

typedef struct {
  uint64_t key;
  char kana[5];
} iolite_keymap;

const PROGMEM iolite_keymap ngmap[] = {
  // 単独
  // {.key = B_T               , .kana = SS_TAP(X_DOWN)},
  // {.key = B_Y               , .kana = SS_TAP(X_UP)},
  // {.key = B_U               , .kana = SS_TAP(X_BSPACE)},
  {.key = B_Q               , .kana = "q"},
  {.key = B_W               , .kana = "ei"},
  {.key = B_E               , .kana = "a"},
  {.key = B_R               , .kana = "ai"},
  {.key = B_T               , .kana = "j"},
  {.key = B_Y               , .kana = "f"},
  {.key = B_U               , .kana = "g"},
  {.key = B_I               , .kana = "k"},
  {.key = B_O               , .kana = "h"},
  {.key = B_P               , .kana = "b"},
  {.key = B_A               , .kana = "l"},
  {.key = B_S               , .kana = "e"},
  {.key = B_D               , .kana = "u"},
  {.key = B_F               , .kana = "i"},
  {.key = B_G               , .kana = "c"},
  {.key = B_H               , .kana = "d"},
  {.key = B_J               , .kana = "t"},
  {.key = B_K               , .kana = "s"},
  {.key = B_L               , .kana = "n"},
  {.key = B_SCLN            , .kana = "z"},
  {.key = B_Z               , .kana = "x"},
  {.key = B_X               , .kana = "ou"},
  {.key = B_C               , .kana = "o"},
  {.key = B_V               , .kana = "uu"},
  {.key = B_B               , .kana = "v"},
  {.key = B_N               , .kana = "y"},
  {.key = B_M               , .kana = "m"},
  {.key = B_COMM            , .kana = "p"},
  {.key = B_DOT             , .kana = "r"},
  {.key = B_SLSH            , .kana = "w"},
  {.key = B_SHFT            , .kana = " "},

  {.key = B_HOME            , .kana = ""},
  {.key = B_PGUP            , .kana = ""},
  {.key = B_PGDN            , .kana = ""},
  {.key = B_END             , .kana = ""},
  {.key = B_TMB1            , .kana = ""},
  {.key = B_TMB2            , .kana = ""},
  {.key = B_TMB3            , .kana = " "},
  {.key = B_TMB4            , .kana = ","},
  {.key = B_TMB5            , .kana = "."},
  {.key = B_TMB6            , .kana = SS_TAP(X_GRV)},
  {.key = B_LEFT            , .kana = SS_TAP(X_LEFT)},
  {.key = B_UP              , .kana = SS_TAP(X_UP)},
  {.key = B_DOWN            , .kana = SS_TAP(X_DOWN)},
  {.key = B_RGHT            , .kana = SS_TAP(X_RGHT)},

  // Left Combo
  {.key = B_E|B_W           , .kana = "altu"},
  {.key = B_F|B_D           , .kana = "iltu"},
  {.key = B_D|B_S           , .kana = "ultu"},
  {.key = B_S|B_A           , .kana = "eltu"},
  {.key = B_C|B_X           , .kana = "oltu"},
  {.key = B_I|B_U           , .kana = SS_TAP(X_LEFT)},
  {.key = B_J|B_H           , .kana = SS_TAP(X_UP)},
  {.key = B_K|B_J           , .kana = SS_TAP(X_DOWN)},
  {.key = B_L|B_K           , .kana = SS_TAP(X_RGHT)},
  {.key = B_LEFT|B_TMB6     , .kana = SS_TAP(X_HOME)},
  {.key = B_UP|B_LEFT       , .kana = SS_TAP(X_PGUP)},
  {.key = B_DOWN|B_UP       , .kana = SS_TAP(X_PGDN)},
  {.key = B_RGHT|B_DOWN     , .kana = SS_TAP(X_END)},

  // Y Layer
  {.key = B_TMB2|B_E        , .kana = "ya"},
  {.key = B_TMB2|B_R        , .kana = "yai"},
  {.key = B_TMB2|B_T        , .kana = "^"},
  {.key = B_TMB2|B_S        , .kana = ";"},
  {.key = B_TMB2|B_D        , .kana = "yu"},
  {.key = B_TMB2|B_F        , .kana = ":"},
  {.key = B_TMB2|B_G        , .kana = "@"},
  {.key = B_TMB2|B_X        , .kana = "you"},
  {.key = B_TMB2|B_C        , .kana = "yo"},
  {.key = B_TMB2|B_V        , .kana = "yuu"},

  {.key = B_TMB2|B_U        , .kana = sym_pair[S_GRV]},
  {.key = B_TMB2|B_I        , .kana = sym_pair[S_BRC]},
  {.key = B_TMB2|B_O        , .kana = sym_pair[S_DQT]},
  {.key = B_TMB2|B_H        , .kana = sym_pair[S_QUOT]},
  {.key = B_TMB2|B_J        , .kana = sym_pair[S_PRN]},
  {.key = B_TMB2|B_K        , .kana = sym_pair[S_LGT]},
  {.key = B_TMB2|B_L        , .kana = sym_pair[S_CBR]},

  {.key = B_TMB2|B_SCLN     , .kana = "~"},
  {.key = B_TMB2|B_M        , .kana = "/"},
  {.key = B_TMB2|B_COMM     , .kana = "|"},
  {.key = B_TMB2|B_DOT      , .kana = "\\"},
  {.key = B_TMB2|B_SLSH     , .kana = "…"},

  // N Layer
  {.key = B_TMB1|B_E        , .kana = "ann"},
  {.key = B_TMB1|B_F        , .kana = "inn"},
  {.key = B_TMB1|B_D        , .kana = "unn"},
  {.key = B_TMB1|B_S        , .kana = "enn"},
  {.key = B_TMB1|B_C        , .kana = "onn"},

  // // enter
  // {.key = B_V|B_M           , .kana = SS_TAP(X_ENTER)},

//   // 編集モード1
//   {.key = B_J|B_K|B_E       , .kana = "deli"},
//   {.key = B_J|B_K|B_R       , .kana = ""},

// #ifdef IOLITE_EDIT_WIN
//   {.key = B_D|B_F|B_I       , .kana = SS_TAP(X_INT4)},
//   {.key = B_J|B_K|B_A       , .kana = SS_LCTRL("y")},
//   {.key = B_J|B_K|B_S       , .kana = SS_LCTRL("s")},
//   {.key = B_J|B_K|B_Z       , .kana = SS_LCTRL("z")},
//   {.key = B_J|B_K|B_X       , .kana = SS_LCTRL("x")},
//   {.key = B_J|B_K|B_C       , .kana = SS_LCTRL("c")},
//   {.key = B_J|B_K|B_V       , .kana = SS_LCTRL("v")},
//   {.key = B_D|B_F|B_SCLN    , .kana = SS_LCTRL("i")},
//   {.key = B_D|B_F|B_SLSH    , .kana = SS_LCTRL("u")},
// #endif
// #ifdef IOLITE_EDIT_MAC
//   {.key = B_D|B_F|B_I       , .kana = SS_TAP(X_LANG1)SS_TAP(X_LANG1)},
//   {.key = B_J|B_K|B_A       , .kana = SS_LGUI("y")},
//   {.key = B_J|B_K|B_S       , .kana = SS_LGUI("s")},
//   {.key = B_J|B_K|B_Z       , .kana = SS_LGUI("z")},
//   {.key = B_J|B_K|B_X       , .kana = SS_LGUI("x")},
//   {.key = B_J|B_K|B_C       , .kana = SS_LGUI("c")},
//   {.key = B_J|B_K|B_V       , .kana = SS_LGUI("v")},
//   {.key = B_D|B_F|B_SCLN    , .kana = SS_LCTRL("k")},
//   {.key = B_D|B_F|B_SLSH    , .kana = SS_LCTRL("j")},
// #endif
//   {.key = B_J|B_K|B_D       , .kana = SS_TAP(X_PGUP)},
//   {.key = B_J|B_K|B_F       , .kana = SS_TAP(X_PGDOWN)},

//   {.key = B_D|B_F|B_O       , .kana = SS_TAP(X_DELETE)},

//   {.key = B_D|B_F|B_J       , .kana = SS_TAP(X_LEFT)},
//   {.key = B_D|B_F|B_M       , .kana = SS_TAP(X_RIGHT)},

//   // 編集モード2
//   {.key = B_M|B_COMM|B_D    , .kana = "!"SS_TAP(X_ENTER)},
//   {.key = B_M|B_COMM|B_F    , .kana = "?"SS_TAP(X_ENTER)},
//   {.key = B_M|B_COMM|B_B    , .kana = "   "},

};

// 薙刀式のレイヤー、シフトキーを設定
void set_iolite(uint8_t layer) {
  iolite_layer = layer;
}

// 薙刀式をオンオフ
void iolite_on(void) {
  is_iolite = true;
  keycomb = 0UL;
  iolite_clear();
  layer_on(iolite_layer);

  tap_code(KC_LANG1); // Mac
  tap_code(KC_HENK); // Win
}

void iolite_off(void) {
  is_iolite = false;
  keycomb = 0UL;
  iolite_clear();
  layer_off(iolite_layer);

  tap_code(KC_LANG2); // Mac
  tap_code(KC_MHEN); // Win
}

// 薙刀式の状態
bool iolite_state(void) {
  return is_iolite;
}


// キー入力を文字に変換して出力する
void iolite_type(void) {
#ifdef IOLITE_JDOUJI
  iolite_keymap_ordered bngmapo; // PROGMEM buffer
#endif
  iolite_keymap bngmap; // PROGMEM buffer
  // iolite_keymap_long bngmapl; // PROGMEM buffer
  // iolite_keymap_unicode bngmapu; // PROGMEM buffer

  uint64_t skey = 0; // 連続押しの場合のバッファ

  switch (keycomb) {
    // send_stringできないキー、長すぎるマクロはここで定義
    case B_F|B_G:
      iolite_off();
      break;
    case B_J|B_K|B_T:
#ifdef IOLITE_EDIT_WIN
      tap_code(KC_HOME);
      for (int i = 0; i < 10; i++) tap_code(KC_RGHT);
#endif
#ifdef IOLITE_EDIT_MAC
      register_code(KC_LGUI);
      tap_code(KC_LEFT);
      unregister_code(KC_LGUI);
      for (int i = 0; i < 10; i++) tap_code(KC_RGHT);
#endif
      break;
    case B_J|B_K|B_G:
#ifdef IOLITE_EDIT_WIN
      tap_code(KC_HOME);
      for (int i = 0; i < 20; i++) tap_code(KC_RGHT);
#endif
#ifdef IOLITE_EDIT_MAC
      register_code(KC_LGUI);
      tap_code(KC_LEFT);
      unregister_code(KC_LGUI);
      for (int i = 0; i < 20; i++) tap_code(KC_RGHT);
#endif
      break;
    case B_J|B_K|B_B:
#ifdef IOLITE_EDIT_WIN
      tap_code(KC_HOME);
      for (int i = 0; i < 30; i++) tap_code(KC_RGHT);
#endif
#ifdef IOLITE_EDIT_MAC
      register_code(KC_LGUI);
      tap_code(KC_LEFT);
      unregister_code(KC_LGUI);
      for (int i = 0; i < 30; i++) tap_code(KC_RGHT);
#endif
      break;
#ifdef IOLITE_EDIT_WIN
    case B_C|B_V|B_P:
      send_unicode_hex_string("FF5C");
      tap_code(KC_ENT);
      tap_code(KC_END);
      send_unicode_hex_string("300A 300B");
      tap_code(KC_ENT);
      tap_code(KC_LEFT);
      break;
    case B_C|B_V|B_Y:
      send_unicode_hex_string("300D");
      tap_code(KC_ENT);
      tap_code(KC_ENT);
      tap_code(KC_SPC);
      break;
    case B_C|B_V|B_H:
      send_unicode_hex_string("300D");
      tap_code(KC_ENT);
      tap_code(KC_ENT);
      send_unicode_hex_string("300C");
      tap_code(KC_ENT);
      break;
    case B_C|B_V|B_N:
      send_unicode_hex_string("300D");
      tap_code(KC_ENT);
      tap_code(KC_ENT);
      break;
#endif
    default:
      // キーから仮名に変換して出力する。
      // 同時押しの場合 ngmapに定義されている

      // // 順序つき
      // #ifdef IOLITE_JDOUJI
      // for (int i = 0; i < sizeof ngmapo / sizeof bngmapo; i++) {
      //   memcpy_P(&bngmapo, &ngmapo[i], sizeof(bngmapo));
      //   if (ninputs[0] == bngmapo.key[0] && ninputs[1] == bngmapo.key[1] && ninputs[2] == bngmapo.key[2]) {
      //     send_string(bngmapo.kana);
      //     iolite_clear();
      //     return;
      //   }
      // }
      // #endif

      // 順序なし
      for (int i = 0; i < sizeof ngmap / sizeof bngmap; i++) {
        memcpy_P(&bngmap, &ngmap[i], sizeof(bngmap));
        if (keycomb == bngmap.key) {
          send_string(bngmap.kana);
          iolite_clear();
          return;
        }
      }

      // // 順序なしロング
      // for (int i = 0; i < sizeof ngmapl / sizeof bngmapl; i++) {
      //   memcpy_P(&bngmapl, &ngmapl[i], sizeof(bngmapl));
      //   if (keycomb == bngmapl.key) {
      //     send_string(bngmapl.kana);
      //     iolite_clear();
      //     return;
      //   }
      // }
      // // 順序なしUNICODE
      // for (int i = 0; i < sizeof ngmapu / sizeof bngmapu; i++) {
      //   memcpy_P(&bngmapu, &ngmapu[i], sizeof(bngmapu));
      //   if (keycomb == bngmapu.key) {
      //     send_unicode_hex_string(bngmapu.kana);
      //     tap_code(KC_ENT);
      //     iolite_clear();
      //     return;
      //   }
      // }

      // 連続押しの場合 ngmapに定義されていない
      for (int j = 0; j < ng_chrcount; j++) {
        skey = ng_key[ninputs[j] - IL_Q];
        if ((keycomb & B_SHFT) > 0) skey |= B_SHFT; // シフトキー状態を反映
        for (int i = 0; i < sizeof ngmap / sizeof bngmap; i++) {
          memcpy_P(&bngmap, &ngmap[i], sizeof(bngmap));
          if (skey == bngmap.key) {
            send_string(bngmap.kana);
            break;
          }
        }
      }
  }

  iolite_clear(); // バッファを空にする
}

// バッファをクリアする
void iolite_clear(void) {
  for (int i = 0; i < ILBUFFER; i++) {
    ninputs[i] = 0;
  }
  ng_chrcount = 0;
}

// 入力モードか編集モードかを確認する
void iolite_mode(uint16_t keycode, keyrecord_t *record) {
  if (!is_iolite) return;

  // modifierが押されたらレイヤーをオフ
  switch (keycode) {
    case KC_LCTRL:
    case KC_LSHIFT:
    case KC_LALT:
    case KC_LGUI:
    case KC_RCTRL:
    case KC_RSHIFT:
    case KC_RALT:
    case KC_RGUI:
      if (record->event.pressed) {
        n_modifier++;
        layer_off(iolite_layer);
      } else {
        n_modifier--;
        if (n_modifier == 0) {
          layer_on(iolite_layer);
        }
      }
      break;
  }

}

bool process_iolite(uint16_t keycode, keyrecord_t *record) {
  // if (!is_iolite || n_modifier > 0) return true;

  if (record->event.pressed) {
    switch (keycode) {
      case IL_Q ... IL_SHFT:
        ninputs[ng_chrcount] = keycode; // キー入力をバッファに貯める
        ng_chrcount++;
        keycomb |= ng_key[keycode - IL_Q]; // キーの重ね合わせ
        // 3文字押したら処理を開始
        if (ng_chrcount > 2) {
          iolite_type();
        }
        return false;
        break;
    }
  } else { // key release
    switch (keycode) {
      case IL_Q ... IL_SHFT:
        // 3文字入力していなくても、どれかキーを離したら処理を開始する
        if (ng_chrcount > 0) {
          iolite_type();
        }
        keycomb &= ~ng_key[keycode - IL_Q]; // キーの重ね合わせ
        return false;
        break;
    }
  }
  return true;
}
