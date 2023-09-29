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

// keyboard layers
enum rainbow_layer_cake {
    _QWERTY,
    _SYMBOL,
    _FUN,
    _NAV,
    _RAT
};

// layer keys
enum rainbow_layer_cake_explorer {
    EK_LEFT = SAFE_RANGE,
    EK_RGHT
};

// the keymap (using MIT Preonic layout)
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_QWERTY] = LAYOUT_preonic_grid(
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSPC,
        KC_ESC,  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,
        KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT,
        KC_LCTL, KC_LGUI, KC_LALT, XXXXXXX, EK_LEFT, KC_SPC,  KC_SPC,  EK_RGHT, XXXXXXX, KC_RALT, KC_RGUI, KC_RCTL
    ),
    [_SYMBOL] = LAYOUT_preonic_grid(
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        KC_TILD, KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC, KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_DEL,
        KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_ENT,
        _______, KC_BSLS, KC_PIPE, KC_PLUS, KC_EQL,  KC_UNDS, KC_MINS, KC_LBRC, KC_LCBR, KC_RCBR, KC_RBRC, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
    ),
    [_FUN] = LAYOUT_preonic_grid(
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        KC_INS,  XXXXXXX, KC_MPRV, KC_MPLY, KC_MNXT, XXXXXXX, XXXXXXX, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_DEL,
        KC_PAUS, KC_LSFT, KC_LALT, KC_LGUI, KC_LCTL, XXXXXXX, KC_CAPS, KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_ENT,
        _______, XXXXXXX, KC_VOLD, KC_MUTE, KC_VOLU, XXXXXXX, XXXXXXX, KC_F9,   KC_F10,  KC_F11,  KC_F12,  _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
    ),
    [_NAV] = LAYOUT_preonic_grid(
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        KC_INS,  XXXXXXX, KC_MPRV, KC_MPLY, KC_MNXT, XXXXXXX, KC_PGUP, KC_HOME, KC_UP,   KC_END,  KC_PGUP, KC_DEL,
        KC_ESC,  KC_LSFT, KC_LALT, KC_LGUI, KC_LCTL, XXXXXXX, KC_PGDN, KC_LEFT, KC_DOWN, KC_RGHT, KC_PGDN, KC_ENT,
        _______, XXXXXXX, KC_VOLD, KC_MUTE, KC_VOLU, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
    ),
    [_RAT] = LAYOUT_preonic_grid(
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        QK_BOOT, XXXXXXX, XXXXXXX, KC_WH_U, KC_PSCR, KC_BTN3, KC_PGUP, KC_HOME, KC_MS_U, KC_END,  KC_PGUP, KC_DEL,
        KC_ESC,  KC_LSFT, KC_ACL0, KC_WH_D, KC_BTN1, KC_BTN2, KC_PGDN, KC_MS_L, KC_MS_D, KC_MS_R, KC_PGDN, KC_ENT,
        _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
    )
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case EK_LEFT:
            if (record->event.pressed) {
                layer_on(_SYMBOL);
                if (IS_LAYER_ON(_FUN)) {
                    layer_on(_RAT);
                }
            } else {
                layer_off(_SYMBOL);
                layer_off(_NAV);
                layer_off(_RAT);
            }
            break;
        case EK_RGHT:
            if (record->event.pressed) {
                layer_on(_FUN);
                if (IS_LAYER_ON(_SYMBOL)) {
                    layer_on(_NAV);
                }
            } else {
                layer_off(_FUN);
                layer_off(_NAV);
                layer_off(_RAT);
            }
            break;
    }
    return true;
}
