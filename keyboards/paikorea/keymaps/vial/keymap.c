// Copyright 2026 Ksty7879
// SPDX-License-Identifier: MIT
//
// Default Vial keymap, taken from the user's saved layout (paikorea.vil).
// Layers live in the keymap below. Tap dances, the combo and the macros are
// Vial's dynamic (EEPROM) entries, so they are written as defaults whenever
// the EEPROM is reset (see "Vial dynamic defaults" at the end of this file).
#include QMK_KEYBOARD_H
#include "dynamic_keymap.h"

enum layers { _BASE, _LOWER, _RAISE, _ADJUST };

/* Tri-layer keys (Vial: FN_MO13 / FN_MO23): LOWER + RAISE = ADJUST */
#define LOWER TL_LOWR
#define RAISE TL_UPPR

#define SFT_Z LSFT_T(KC_Z)

/* Tap dances (Vial dynamic entries, defaults below) */
#define TD_ENT TD(0) // tap Enter
#define TD_S   TD(1) // tap S, hold Left Ctrl
#define TD_D   TD(2) // tap D, hold Left Shift
#define TD_F   TD(3) // tap F, hold Left Alt (500 ms)
#define TD_K   TD(4) // tap K, hold Right Shift
#define TD_L   TD(5) // tap L, hold Right Ctrl
#define TD_B   TD(7) // tap B, hold RAISE

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /*
     * ,----------------------------------.          ,----------------------------------.
     * |   Q  |   W  |   E  |   R  |   T  |  [pad]   |   Y  |   U  |   I  |   O  |   P  |
     * |------+------+------+------+------|          |------+------+------+------+------|
     * |   A  |S/Ctl |D/Sft |F/Alt |   G  |          |   H  |   J  |K/Sft |L/Ctl |   ;  |
     * |------+------+------+------+------|          |------+------+------+------+------|
     * |Sft/Z |   X  |   C  |   V  |B/RAIS|          |   N  |   M  |   ,  |   .  |   /  |
     * `------+------+------+------+------+------.   ,------+------+------+------+------'
     * | Ctrl |             |Enter |Space |LOWER |   |RAISE |Space | Bksp |      | RAlt |
     * `------'             `--------------------'   `--------------------'      `------'
     *  Combo: N + M = B
     */
    [_BASE] = LAYOUT(
        KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                 KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,
        KC_A,    TD_S,    TD_D,    TD_F,    KC_G,                 KC_H,    KC_J,    TD_K,    TD_L,    KC_SCLN,
        SFT_Z,   KC_X,    KC_C,    KC_V,    TD_B,                 KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,
        KC_LCTL,          TD_ENT,  KC_SPC,  LOWER,       RAISE,   KC_SPC,  KC_BSPC,                   KC_RALT
    ),
    /*
     * LOWER: numbers, arrows, media
     * |   1  |   2  |   3  |   4  |   5  |          |   6  |   7  |   8  |   9  |   0  |
     * | Sft  | Del  |  Up  | Vol- | Vol+ |          |      |   4  |   5  |   6  | Del  |
     * | Ctrl | Left | Down |Right | Play |          |      |   1  |   2  |   3  |      |
     * |      |             | Tab  |Space |      |   |      |      |   0  |      | 한자 |
     */
    [_LOWER] = LAYOUT(
        KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                 KC_6,    KC_7,    KC_8,    KC_9,    KC_0,
        KC_LSFT, KC_DEL,  KC_UP,   KC_VOLD, KC_VOLU,              XXXXXXX, KC_4,    KC_5,    KC_6,    KC_DEL,
        KC_LCTL, KC_LEFT, KC_DOWN, KC_RGHT, KC_MPLY,              _______, KC_1,    KC_2,    KC_3,    _______,
        _______,          KC_TAB,  KC_SPC,  _______,     _______, _______, KC_0,                      KC_LNG2
    ),
    /*
     * RAISE: F-keys, symbols, macros
     * | Esc  | F10  | F11  | F12  |  \   |          |  '   |      |      |      | Bksp |
     * |  M1  |  F7  |  F8  |  F9  |  |   |          |  -   |  =   |  [   |  ]   |  `   |
     * |  M0  |  F4  |  F5  |  F6  |      |          |  _   |  +   |  {   |  }   |Enter |
     * |      |             |  F1  |  F2  |  F3  |   |      |      |      |      |      |
     *  M0 = Ctrl+Shift+Esc, M1 = Win+Shift+S
     */
    [_RAISE] = LAYOUT(
        KC_ESC,  KC_F10,  KC_F11,  KC_F12,  KC_BSLS,              KC_QUOT, XXXXXXX, XXXXXXX, XXXXXXX, KC_BSPC,
        MC_1,    KC_F7,   KC_F8,   KC_F9,   KC_PIPE,              KC_MINS, KC_EQL,  KC_LBRC, KC_RBRC, KC_GRV,
        MC_0,    KC_F4,   KC_F5,   KC_F6,   _______,              KC_UNDS, KC_PLUS, KC_LCBR, KC_RCBR, KC_ENT,
        _______,          KC_F1,   KC_F2,   KC_F3,       _______, _______, _______,                   _______
    ),
    /* LOWER + RAISE: empty (all transparent) */
    [_ADJUST] = LAYOUT(
        _______, _______, _______, _______, _______,              _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______,              _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______,              _______, _______, _______, _______, _______,
        _______,          _______, _______, _______,     _______, _______, _______,                   _______
    ),
};
// clang-format on

/* ---------------------------------------------------------------------------
 * Vial dynamic defaults
 *
 * Vial keeps tap dances, combos and macros in EEPROM and clears them whenever
 * the EEPROM is reset: after flashing a new build (Vial's EEPROM magic is a
 * per-build ID) or after QK_CLEAR_EEPROM / Bootmagic. Both cases are caught
 * below and the entries are written back once the keyboard has started.
 * Changes made later in Vial are kept until the next reset.
 * ------------------------------------------------------------------------- */
static bool vial_defaults_pending = false;

/* Runs before VIA checks its EEPROM magic. */
void via_init_kb(void) {
    if (!via_eeprom_is_valid()) {
        vial_defaults_pending = true;
    }
}

/* Runs after a full EEPROM reset (QK_CLEAR_EEPROM, Bootmagic). */
void eeconfig_init_user(void) {
    vial_defaults_pending = true;
}

static void write_vial_defaults(void) {
    /* {tap, hold, double tap, tap+hold, tapping term ms} */
    static const vial_tap_dance_entry_t tap_dances[] = {
        [0] = {KC_ENT, KC_NO, KC_NO, KC_NO, 200},
        [1] = {KC_S, KC_LCTL, KC_NO, KC_NO, 130},
        [2] = {KC_D, KC_LSFT, KC_NO, KC_NO, 130},
        [3] = {KC_F, KC_LALT, KC_NO, KC_NO, 500},
        [4] = {KC_K, KC_RSFT, KC_NO, KC_NO, 130},
        [5] = {KC_L, KC_RCTL, KC_NO, KC_NO, 130},
        [6] = {KC_NO, KC_NO, KC_NO, KC_NO, 200},
        [7] = {KC_B, RAISE, KC_NO, KC_NO, 200},
    };
    for (uint8_t i = 0; i < ARRAY_SIZE(tap_dances); i++) {
        dynamic_keymap_set_tap_dance(i, &tap_dances[i]);
    }

    /* {{keys}, output} */
    static const vial_combo_entry_t combos[] = {
        {{KC_N, KC_M, KC_NO, KC_NO}, KC_B},
    };
    for (uint8_t i = 0; i < ARRAY_SIZE(combos); i++) {
        dynamic_keymap_set_combo(i, &combos[i]);
    }

    /* Macro strings, each ended by a NUL: M0 = Ctrl+Shift+Esc, M1 = Win+Shift+S */
    static uint8_t macros[] =
        SS_DOWN(X_LCTL) SS_DOWN(X_LSFT) SS_TAP(X_ESC) SS_TAP(X_LCTL) SS_UP(X_LCTL) SS_UP(X_LSFT) "\0"
        SS_DOWN(X_LGUI) SS_DOWN(X_LSFT) SS_TAP(X_S) SS_UP(X_LGUI) SS_UP(X_LSFT);
    dynamic_keymap_macro_set_buffer(0, sizeof(macros), macros);

    /* Load the new tap dances and combos into RAM. */
    vial_init();
}

void keyboard_post_init_user(void) {
    if (vial_defaults_pending) {
        vial_defaults_pending = false;
        write_vial_defaults();
    }
}
