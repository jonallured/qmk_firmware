#include QMK_KEYBOARD_H

enum layers {
  _BASE,
  _FUNCTION,
  _RGB
};

enum keycodes {
  HYPER = SAFE_RANGE
};

// Layer Toggle
#define T_RGB TG(_RGB)

// Open Emoji pane
#define EMOJI LCTL(LGUI(KC_SPC))

// hold for layer switch and tap for space
#define SPC_FUNC LT(_FUNCTION, KC_SPC)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_BASE] = LAYOUT_all(
      KC_ESC,  KC_1, KC_2, KC_3, KC_4, KC_5, KC_6,          KC_7, KC_8, KC_9, KC_0,    KC_MINS, KC_EQL,  KC_BSPC, KC_DEL,           KC_MUTE,
      KC_TAB,        KC_Q, KC_W, KC_E, KC_R, KC_T,          KC_Y, KC_U, KC_I, KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS,          KC_DEL,
      KC_LCTL,       KC_A, KC_S, KC_D, KC_F, KC_G,          KC_H, KC_J, KC_K, KC_L,    KC_SCLN, KC_QUOT, KC_ENT,                    KC_PGUP,
      KC_LSFT,       KC_Z, KC_X, KC_C, KC_V, KC_B,          KC_B, KC_N, KC_M, KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT,          KC_UP,   KC_PGDN,
      HYPER, KC_LALT,          KC_LGUI,    SPC_FUNC,        SPC_FUNC,     MO(_FUNCTION),                KC_RGUI, KC_RCTL, KC_LEFT, KC_DOWN, KC_RGHT
  ),
  [_FUNCTION] = LAYOUT_all(
      KC_GRAVE,    _______, _______, _______, _______, _______, _______,          _______, _______, _______, _______, _______, _______, _______, _______,          T_RGB,
      _______,           _______, _______, _______, _______, _______,          _______, _______, _______, _______, _______, _______, _______, _______,          _______,
      _______,           _______, _______, _______, _______, _______,          KC_LEFT, KC_DOWN, KC_UP, KC_RGHT, _______, _______, RESET,                   _______,
      _______,           _______, _______, _______, _______, _______,          _______, _______, _______, _______, _______, _______, _______,          _______, _______,
      RGB_TOG, _______,                             _______, _______,          _______, EMOJI,                            _______, _______, _______, _______, _______
  ),
  [_RGB] = LAYOUT_all(
      _______,  RGB_M_P, RGB_M_B, RGB_M_R, RGB_M_SW, RGB_M_SN, RGB_M_K,          RGB_M_X, RGB_M_G, RGB_M_T, _______, _______, _______, _______, _______,           _______,
      _______,           _______, _______, _______,  _______,  _______,          _______, _______, _______, _______, _______, _______, _______, _______,           _______,
      _______,           _______, RGB_SAI, RGB_SAD,  _______,  _______,          RGB_HUI, RGB_HUD, _______, _______, _______, _______, RGB_TOG,                    _______,
      _______,           _______, _______, _______,  RGB_VAI,  RGB_VAD,          _______, _______, _______, _______, _______, _______, _______,           _______, _______,
      _______, _______,                              _______,  _______,          _______, _______,                            _______, _______, RGB_RMOD, _______, RGB_MOD
  ),
  
};

bool encoder_update_user(uint8_t index, bool clockwise) {
    if (index == 0) {
      if (clockwise) {
          tap_code(KC_VOLD);
      } else {
          tap_code(KC_VOLU);
      };
    };
    return false;
};

/* bool encoder_update_user(uint8_t index, bool clockwise) { */
/*     if (index == 0) { */
/*         if (IS_LAYER_ON(_MAC)) { */
/*             if (clockwise) { */
/*                 tap_code16(LCMD(KC_Z)); */
/*             } else { */
/*                 tap_code16(LCMD(LSFT(KC_Z))); */
/*             }; */
/*         } else { */
/*             if (clockwise) { */
/*                 tap_code(KC_VOLD); */
/*             } else { */
/*                 tap_code(KC_VOLU); */
/*             }; */
/*         }; */
/*     }; */
/*     return false; */
/* }; */

#ifdef OLED_ENABLE
bool oled_task_user(void) {
    // Host Keyboard Layer Status
    oled_write_P(PSTR("Layer: "), false);

    switch (get_highest_layer(layer_state)) {
        case _BASE:
            oled_write_P(PSTR("Default\n"), false);
            break;
        case _FUNCTION:
            oled_write_P(PSTR("Function\n"), false);
            break;
        case _RGB:
            oled_write_P(PSTR("RGB\n"), false);
            break;
        default:
            // Or use the write_ln shortcut over adding '\n' to the end of your string
            oled_write_ln_P(PSTR("Undefined"), false);
    }

    // Host Keyboard LED Status
    led_t led_state = host_keyboard_led_state();
    oled_write_P(led_state.num_lock ? PSTR("NUM ") : PSTR("    "), false);
    oled_write_P(led_state.caps_lock ? PSTR("CAP ") : PSTR("    "), false);
    oled_write_P(led_state.scroll_lock ? PSTR("SCR ") : PSTR("    "), false);
    
    return false;
}
#endif

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
    case HYPER:
        if (record->event.pressed) {
            register_code(KC_LEFT_SHIFT)
            register_code(KC_LEFT_ALT)
            register_code(KC_LEFT_CTRL)
            register_code(KC_LCMD)
        } else {
            unregister_code(KC_LEFT_SHIFT)
            unregister_code(KC_LEFT_ALT)
            unregister_code(KC_LEFT_CTRL)
            unregister_code(KC_LCMD)
        }
        break;
    }
    return true;
};
