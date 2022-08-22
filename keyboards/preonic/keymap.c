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
    TOP,
    FUN,
    EXT,
    NAV,
    RAT
};

// the keymap
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [TOP] = LAYOUT_preonic_grid(
        MO(FUN), KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    MO(FUN),
        KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSPC,
        KC_ESC,  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,
        KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT,
        KC_LCTL, KC_LGUI, KC_LALT, MO(FUN), MO(NAV), KC_SPC,  KC_SPC,  MO(EXT), MO(FUN), KC_RALT, KC_RGUI, KC_RCTL
        ),
    [FUN] = LAYOUT_preonic_grid(
        _______, KC_MPRV, KC_MPLY, KC_MNXT, NK_ON,   XXXXXXX, XXXXXXX, NK_OFF,  KC_MUTE, KC_VOLD, KC_VOLU, _______,
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,
        _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______,
        _______, _______, _______, _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______, _______, _______, _______
        ),
    [EXT] = LAYOUT_preonic_grid(
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_PSCR,
        KC_INS,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_DEL,
        KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_ENT,
        _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_MINS, KC_EQL,  KC_LBRC, KC_RBRC, KC_BSLS, _______,
        _______, _______, _______, XXXXXXX, _______, _______, _______, _______, XXXXXXX, _______, _______, _______
        ),
    [NAV] = LAYOUT_preonic_grid(
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_PSCR,
        XXXXXXX, XXXXXXX, KC_UP,   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_PGUP, XXXXXXX, XXXXXXX, KC_DEL,
        KC_ESC,  KC_LEFT, KC_DOWN, KC_RGHT, XXXXXXX, XXXXXXX, XXXXXXX, KC_HOME, KC_PGDN, KC_END,  XXXXXXX, KC_ENT,
        _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______,
        _______, _______, _______, XXXXXXX, _______, _______, _______, _______, XXXXXXX, _______, _______, _______
        ),
    [RAT] = LAYOUT_preonic_grid(
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_PSCR,
        XXXXXXX, XXXXXXX, KC_MS_U, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_WH_U, KC_BTN3, XXXXXXX, KC_DEL,
        KC_ESC,  KC_MS_L, KC_MS_D, KC_MS_R, XXXXXXX, XXXXXXX, XXXXXXX, KC_BTN1, KC_WH_D, KC_BTN2, KC_ACL0, KC_ENT,
        _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______,
        _______, _______, _______, XXXXXXX, _______, _______, _______, _______, XXXXXXX, _______, _______, _______
        )
};

// activation for RAT layer
layer_state_t layer_state_set_user(layer_state_t state) {
    return update_tri_layer_state(state, EXT, NAV, RAT);
}
