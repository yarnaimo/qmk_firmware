#ifndef KEYMAP_XROWS_H
#define KEYMAP_XROWS_H

#include "keymap_jp.h"
#include "edvorakjp.h"
/*
 * enum custom_keycodes {
 *   KC_LOCK = NEW_SAFE_RANGE,
 * };
 */

#define KC_ KC_TRNS
#define KC_RESET RESET

#define KC_TMB1 KC_LA(TAB)
#define KC_TMB2 KC_LS(SPC)
#define KC_TMB3 LT(_LOWER, KC_MHEN) // act as LOWER when hold, as KC_LANG2(=English) when tapped
#define KC_TMB4 LT(_RAISE, KC_HENK) // act as RAISE when hold, as KC_LANG1(=Japanese) when tapped
#define KC_TMB5 KC_RC(BSPC)
#define KC_TMB6 KC_RG(ENT)
#define KC_TMB7 KC_RC(DEL)

#endif
