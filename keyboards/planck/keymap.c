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

// delicious layers
enum rainbow_layer_cake {
    TXT,
    EXT,
    NAV,
    RAT
};

// make SHIFT+KC_MPRV output KC_VOLU
const key_override_t kc_volu_override = ko_make_with_layers_and_negmods(
    MOD_MASK_SHIFT,
    KC_MPRV,
    KC_VOLU,
    ~0,
    MOD_MASK_CAG
);

// make SHIFT+KC_MNXT output KC_VOLD
const key_override_t kc_vold_override = ko_make_with_layers_and_negmods(
    MOD_MASK_SHIFT,
    KC_MNXT,
    KC_VOLD,
    ~0,
    MOD_MASK_CAG
);

// make SHIFT+KC_MPLY output KC_MUTE
const key_override_t kc_mute_override = ko_make_with_layers_and_negmods(
    MOD_MASK_SHIFT,
    KC_MPLY,
    KC_MUTE,
    ~0,
    MOD_MASK_CAG
);

// define all key overrides
const key_override_t **key_overrides = (const key_override_t *[]) {
    &kc_volu_override,
    &kc_vold_override,
    &kc_mute_override,
    NULL
};

// keyboard and mouse combo
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [TXT] = LAYOUT_preonic_grid(
        KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSPC,
        KC_ESC,  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,
        KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT,
        KC_LCTL, KC_LGUI, KC_LALT, KC_LSFT, MO(EXT), KC_SPC,  KC_SPC,  MO(NAV), KC_RSFT, KC_RALT, KC_RGUI, KC_RCTL
        ),
    [EXT] = LAYOUT_preonic_grid(
        KC_TILD, KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC, KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_DEL,
        KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_ENT,
        _______, KC_PIPE, KC_LCBR, KC_RCBR, KC_PLUS, KC_UNDS, KC_MINS, KC_EQL,  KC_LBRC, KC_RBRC, KC_BSLS, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
        ),
    [NAV] = LAYOUT_preonic_grid(
        KC_INS,  KC_HOME, KC_UP,   KC_END,  KC_PGUP, XXXXXXX, XXXXXXX, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_DEL,
        KC_PSCR, KC_LEFT, KC_DOWN, KC_RGHT, KC_PGDN, XXXXXXX, XXXXXXX, KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_ENT,
        _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_F9,   KC_F10,  KC_F11,  KC_F12,  _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
        ),
    [RAT] = LAYOUT_preonic_grid(
        NK_ON,   KC_HOME, KC_MS_U, KC_END,  KC_PGUP, XXXXXXX, XXXXXXX, XXXXXXX, KC_WH_U, KC_BTN3, XXXXXXX, NK_OFF,
        GUI_ON,  KC_MS_L, KC_MS_D, KC_MS_R, KC_PGDN, XXXXXXX, KC_MPRV, KC_BTN1, KC_WH_D, KC_BTN2, KC_ACL0, GUI_OFF,
        _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_MNXT, KC_MPLY, XXXXXXX, XXXXXXX, XXXXXXX, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
        )
};

// activation for RAT layer
layer_state_t layer_state_set_user(layer_state_t state) {
    return update_tri_layer_state(state, EXT, NAV, RAT);
}
