/*
Copyright 2022 Edward Kopp <edward@edwardkopp.com>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program. If not, see <https://www.gnu.org/licenses/>.
*/

#include QMK_KEYBOARD_H

enum rainbow_layer_cake {
    CRINGE,
    BASED,
    SYMBOL,
    FUNCTION,
    RAT
};

#define EK_LEFT MO(SYMBOL)
#define EK_RGHT MO(FUNCTION)
#define EK_CRY DF(CRINGE)
#define EK_YES DF(BASED)

// make SHIFT+KC_MPLY output KC_MUTE
const key_override_t kc_mute_override = ko_make_with_layers_and_negmods(
    MOD_MASK_SHIFT,
    KC_MPLY,
    KC_MUTE,
    ~0,
    MOD_MASK_CAG
);

// make SHIFT+KC_MPRV output KC_VOLD
const key_override_t kc_vold_override = ko_make_with_layers_and_negmods(
    MOD_MASK_SHIFT,
    KC_MPRV,
    KC_VOLD,
    ~0,
    MOD_MASK_CAG
);

// make SHIFT+KC_MNXT output KC_VOLU
const key_override_t kc_volu_override = ko_make_with_layers_and_negmods(
    MOD_MASK_SHIFT,
    KC_MNXT,
    KC_VOLU,
    ~0,
    MOD_MASK_CAG
);

// define all key overrides
const key_override_t **key_overrides = (const key_override_t *[]) {
    &kc_mute_override,
    &kc_vold_override,
    &kc_volu_override,
    NULL
};

// remove first row on each layer and it's literally the planck keymap
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [CRINGE] = LAYOUT_preonic_grid(
        KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MPLY,
        KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSPC,
        KC_DEL,  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,
        KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT,
        KC_LCTL, KC_LALT, KC_LGUI, KC_ESC,  EK_LEFT, KC_SPC,  KC_SPC,  EK_RGHT, KC_ENT,  KC_RGUI, KC_RALT, KC_RCTL
    ),
    [BASED] = LAYOUT_preonic_grid(
        KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MPLY,
        KC_TAB,  KC_Q,    KC_W,    KC_F,    KC_P,    KC_B,    KC_J,    KC_L,    KC_U,    KC_Y,    KC_SCLN, KC_BSPC,
        KC_DEL,  KC_A,    KC_R,    KC_S,    KC_T,    KC_G,    KC_M,    KC_N,    KC_E,    KC_I,    KC_O,    KC_QUOT,
        KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_D,    KC_V,    KC_K,    KC_H,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT,
        KC_LCTL, KC_LALT, KC_LGUI, KC_ESC,  EK_LEFT, KC_SPC,  KC_SPC,  EK_RGHT, KC_ENT,  KC_RGUI, KC_RALT, KC_RCTL
    ),
    [SYMBOL] = LAYOUT_preonic_grid(
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        KC_TILD, KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC, KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_PIPE,
        KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_BSLS,
        _______, KC_MPRV, KC_MNXT, KC_UNDS, KC_MINS, KC_PLUS, KC_EQL,  KC_LBRC, KC_RBRC, KC_LCBR, KC_RCBR, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
    ),
    [FUNCTION] = LAYOUT_preonic_grid(
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        NK_ON,   XXXXXXX, KC_HOME, KC_UP,   KC_END,  XXXXXXX, XXXXXXX, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_INS,
        GUI_ON,  XXXXXXX, KC_LEFT, KC_DOWN, KC_RGHT, KC_PGUP, XXXXXXX, KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_PAUS,
        _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_PGDN, XXXXXXX, KC_F9,   KC_F10,  KC_F11,  KC_F12,  _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
    ),
    [RAT] = LAYOUT_preonic_grid(
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        NK_OFF,  XXXXXXX, XXXXXXX, KC_MS_U, XXXXXXX, XXXXXXX, QK_BOOT, XXXXXXX, KC_WH_U, KC_BTN3, XXXXXXX, KC_CALC,
        GUI_OFF, XXXXXXX, KC_MS_L, KC_MS_D, KC_MS_R, XXXXXXX, EK_YES,  KC_BTN1, KC_WH_D, KC_BTN2, KC_ACL0, KC_PSCR,
        _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, EK_CRY,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
    )
};

layer_state_t layer_state_set_user(layer_state_t state) {
    return update_tri_layer_state(state, SYMBOL, FUNCTION, RAT);
}
