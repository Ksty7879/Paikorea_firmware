// Copyright 2026 Ksty7879
// SPDX-License-Identifier: MIT
#include QMK_KEYBOARD_H

enum layers { _BASE, _LOWER, _RAISE, _ADJUST };

#define LOWER MO(_LOWER)
#define RAISE MO(_RAISE)
#define SFT_Z LSFT_T(KC_Z)
#define SFT_SL RSFT_T(KC_SLSH)

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /*
     * ,----------------------------------.          ,----------------------------------.
     * |   Q  |   W  |   E  |   R  |   T  |  [pad]   |   Y  |   U  |   I  |   O  |   P  |
     * |------+------+------+------+------|          |------+------+------+------+------|
     * |   A  |   S  |   D  |   F  |   G  |          |   H  |   J  |   K  |   L  |   ;  |
     * |------+------+------+------+------|          |------+------+------+------+------|
     * |Sft/Z |   X  |   C  |   V  |   B  |          |   N  |   M  |   ,  |   .  |Sft// |
     * `------+------+------+------+------+------.   ,------+------+------+------+------'
     * | Ctrl |             | GUI  |LOWER |Space |   |Enter |RAISE | Bksp |      |한/영 |
     * `------'             `--------------------'   `--------------------'      `------'
     */
    [_BASE] = LAYOUT(
        KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                 KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,
        KC_A,    KC_S,    KC_D,    KC_F,    KC_G,                 KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN,
        SFT_Z,   KC_X,    KC_C,    KC_V,    KC_B,                 KC_N,    KC_M,    KC_COMM, KC_DOT,  SFT_SL,
        KC_LCTL,          KC_LGUI, LOWER,   KC_SPC,      KC_ENT,  RAISE,   KC_BSPC,                   KC_LNG1
    ),
    /* numbers & symbols */
    [_LOWER] = LAYOUT(
        KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                 KC_6,    KC_7,    KC_8,    KC_9,    KC_0,
        KC_ESC,  KC_LALT, KC_GRV,  KC_MINS, KC_EQL,               KC_LBRC, KC_RBRC, KC_BSLS, KC_QUOT, KC_DEL,
        KC_TAB,  _______, _______, _______, _______,              _______, _______, _______, _______, _______,
        _______,          _______, _______, _______,     _______, _______, _______,                   KC_LNG2
    ),
    /* F-keys & navigation */
    [_RAISE] = LAYOUT(
        KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,                KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,
        KC_F11,  KC_F12,  KC_PSCR, KC_INS,  KC_CAPS,              KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, KC_DEL,
        _______, _______, _______, _______, _______,              KC_HOME, KC_PGDN, KC_PGUP, KC_END,  _______,
        _______,          _______, _______, _______,     _______, _______, _______,                   _______
    ),
    /* LOWER + RAISE: mouse, media, trackpad, bootloader */
    [_ADJUST] = LAYOUT(
        QK_BOOT, _______, _______, _______, _______,              _______, _______, _______, _______, QK_BOOT,
        _______, KC_MPRV, KC_MPLY, KC_MNXT, _______,              MS_BTN1, MS_BTN3, MS_BTN2, DRG_SCRL, PAD_SWAP,
        _______, KC_VOLD, KC_MUTE, KC_VOLU, _______,              _______, _______, _______, _______, _______,
        _______,          _______, _______, _______,     _______, _______, _______,                   _______
    ),
};
// clang-format on

layer_state_t layer_state_set_user(layer_state_t state) {
    return update_tri_layer_state(state, _LOWER, _RAISE, _ADJUST);
}
