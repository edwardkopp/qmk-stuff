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

// remove first row on each layer and it's literally the planck keymap
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT_preonic_grid(
        KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MPLY,
        KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSPC,
        KC_ESC,  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,
        KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT,
        KC_LCTL, KC_LALT, KC_LSFT, KC_LGUI, MO(1),   KC_SPC,  KC_SPC,  MO(2),   KC_RGUI, KC_RSFT, KC_RALT, KC_RCTL
        ),
    [1] = LAYOUT_preonic_grid(
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        KC_INS,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_MUTE, KC_VOLD, KC_VOLU, KC_PIPE, KC_DEL,
        KC_TILD, KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC, KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_ENT,
        _______, KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_UNDS, KC_PLUS, KC_LCBR, KC_RCBR, _______,
        _______, _______, _______, _______, _______, KC_UNDS, KC_UNDS, _______, _______, _______, _______, _______
        ),
    [2] = LAYOUT_preonic_grid(
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        KC_INS,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_MPLY, KC_MPRV, KC_MNXT, KC_BSLS, KC_DEL,
        KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_ENT,
        _______, KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_MINS, KC_EQL,  KC_LBRC, KC_RBRC, _______,
        _______, _______, _______, _______, _______, KC_MINS, KC_MINS, _______, _______, _______, _______, _______
        ),
    [3] = LAYOUT_preonic_grid(
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        GUI_TOG, XXXXXXX, KC_HOME, KC_MS_U, KC_END,  XXXXXXX, XXXXXXX, KC_HOME, KC_UP,   KC_END,  XXXXXXX, KC_DEL,
        KC_PSCR, XXXXXXX, KC_MS_L, KC_MS_D, KC_MS_R, KC_PGUP, KC_WH_U, KC_LEFT, KC_DOWN, KC_RGHT, NK_TOGG, KC_ENT,
        _______, KC_LSFT, KC_LCTL, KC_LALT, KC_LGUI, KC_PGDN, KC_WH_D, KC_BTN1, KC_BTN2, KC_BTN3, XXXXXXX, _______,
        _______, _______, _______, _______, _______, KC_SPC,  KC_SPC,  _______, _______, _______, _______, _______
        )
};

// activation for RAT layer
layer_state_t layer_state_set_user(layer_state_t state) {
    state = update_tri_layer_state(state, 1, 2, 3);
    return state
}
