void iolite_type(void);
void iolite_clear(void);

void iolite_mode(uint16_t, keyrecord_t *);

void iolite_on(void);
void iolite_off(void);
bool iolite_state(void);

bool process_iolite(uint16_t, keyrecord_t *);
void set_iolite(uint8_t);

typedef enum iolite_keycodes {
  IL_Q = SAFE_RANGE, // 薙刀式シフトキー
  IL_W,
  IL_E,
  IL_R,
  IL_T,
  IL_Y,
  IL_U,
  IL_I,
  IL_O,
  IL_P,

  IL_A,
  IL_S,
  IL_D,
  IL_F,
  IL_G,
  IL_H,
  IL_J,
  IL_K,
  IL_L,
  IL_SCLN,

  IL_Z,
  IL_X,
  IL_C,
  IL_V,
  IL_B,
  IL_N,
  IL_M,
  IL_COMM,
  IL_DOT,
  IL_SLSH,

  IL_SHFT,

  IL_HOME,
  IL_PGUP,
  IL_PGDN,
  IL_END,
  IL_TMB1,
  IL_TMB2,
  IL_TMB3,

  IL_TMB4,
  IL_TMB5,
  IL_TMB6,
  IL_LEFT,
  IL_UP,
  IL_DOWN,
  IL_RGHT,
} ILKEYS;

#define IL_SAFE_RANGE SAFE_RANGE+63

#define KC_ILSHFT ILSHFT
