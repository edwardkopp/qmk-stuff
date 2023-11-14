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


// The layers
enum rainbow_layer_cake
{
    _QWERTY,
    _GAME,
    _SYMBOL,
    _NAV,
    _RAT,
    _RMOD,
    _LMOD
};


// Keycodes for exploration of the rainbow layer cake
#define EK_SYM MO(_SYMBOL)
#define EK_NAV MO(_NAV)
#define EK_LMOD MO(_LMOD)
#define EK_RMOD MO(_RMOD)


// Keycodes requiring code implementation for basic functionality
enum rainbow_sprinkles
{
    EK_GAME = SAFE_RANGE,
    EK_GOFF
};


// Single modifier keycodes associated with the modifier layers
#define EK_GUI KC_LGUI
#define EK_LCTL KC_LCTL
#define EK_LALT KC_LALT
#define EK_RCTL KC_RCTL
#define EK_RALT KC_RALT


// Special keycodes associated with the modifier layers
#define EK_CS S(KC_LCTL)
#define EK_GS S(KC_LGUI)
#define EK_AS S(KC_LALT)
#define EK_CG C(KC_LGUI)
#define EK_CA C(KC_LALT)
#define EK_GA A(KC_LGUI)
#define EK_CGS C(S(KC_LGUI))
#define EK_CAS C(A(KC_LSFT))
#define EK_GAS A(S(KC_LGUI))
#define EK_CGA C(A(KC_LGUI))
#define EK_____ _______
#define EK_BOOT QK_BOOT


// Tuple for referencing these special modifiers
const uint16_t specialModifiers[] = {
    EK_GUI,
    EK_LCTL,
    EK_LALT,
    EK_RCTL,
    EK_RALT,
    EK_CS,
    EK_GS,
    EK_AS,
    EK_CG,
    EK_CA,
    EK_GA,
    EK_CGS,
    EK_CAS,
    EK_GAS,
    EK_CGA,
    EK_____,
    EK_BOOT
};


// Calculate the keycode count of the tuple
size_t specialModifiersCount = sizeof(specialModifiers) / sizeof(specialModifiers[0]);


// The keymap
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_QWERTY] = LAYOUT_preonic_grid(
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSPC,
        KC_ESC,  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,
        EK_LMOD, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, EK_RMOD,
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, EK_SYM,  KC_SPC,  KC_SPC,  EK_NAV,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX
    ),
    [_GAME] = LAYOUT_preonic_grid(
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        KC_LSFT, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        KC_LCTL, KC_LGUI, KC_LALT, XXXXXXX, _______, _______, _______, _______, _______, _______, _______, _______
    ),
    [_SYMBOL] = LAYOUT_preonic_grid(
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        KC_TILD, KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC, KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_DEL,
        KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_ENT,
        _______, KC_BSLS, KC_PIPE, KC_PLUS, KC_EQL,  KC_UNDS, KC_MINS, KC_LBRC, KC_LCBR, KC_RCBR, KC_RBRC, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
    ),
    [_NAV] = LAYOUT_preonic_grid(
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        KC_INS,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   XXXXXXX, XXXXXXX, KC_HOME, KC_UP,   KC_END,  KC_MPRV, KC_DEL,
        KC_PAUS, KC_F5,   KC_F6,   KC_F7,   KC_F8,   XXXXXXX, XXXXXXX, KC_LEFT, KC_DOWN, KC_RGHT, KC_MPLY, KC_ENT,
        _______, KC_F9,   KC_F10,  KC_F11,  KC_F12,  XXXXXXX, XXXXXXX, KC_PGUP, KC_CAPS, KC_PGDN, KC_MNXT, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
    ),
    [_RAT] = LAYOUT_preonic_grid(
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        XXXXXXX, KC_VOLU, XXXXXXX, KC_WH_U, KC_BTN2, XXXXXXX, XXXXXXX, KC_HOME, KC_MS_U, KC_END,  KC_MPRV, KC_DEL,
        KC_ESC,  KC_MUTE, KC_ACL0, KC_WH_D, KC_BTN1, XXXXXXX, XXXXXXX, KC_MS_L, KC_MS_D, KC_MS_R, KC_MPLY, KC_ENT,
        _______, KC_VOLD, XXXXXXX, KC_BTN3, XXXXXXX, XXXXXXX, XXXXXXX, KC_PGUP, KC_PSCR, KC_PGDN, KC_MNXT, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
    ),
    [_RMOD] = LAYOUT_preonic_grid(
        _______, _______, _______, _______, _______, _______, EK_____, EK_____, EK_____, EK_____, EK_____, EK_____,
        _______, _______, _______, _______, _______, _______, EK_CGS,  EK_CS,   EK_GS,   EK_AS,   EK_____, EK_BOOT,
        _______, _______, _______, _______, _______, _______, EK_CAS,  EK_RCTL, EK_GUI,  EK_RALT, EK_CGA,  EK_____,
        EK_GOFF, _______, _______, _______, _______, _______, EK_GAS,  EK_CG,   EK_CA,   EK_GA,   EK_____, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX
    ),
    [_LMOD] = LAYOUT_preonic_grid(
        EK_____, EK_____, EK_____, EK_____, EK_____, EK_____, _______, _______, _______, _______, _______, _______,
        EK_BOOT, EK_____, EK_AS,   EK_GS,   EK_CS,   EK_CGS,  _______, _______, _______, _______, _______, _______,
        EK_____, EK_CGA,  EK_LALT, EK_GUI,  EK_LCTL, EK_CAS,  _______, _______, _______, _______, _______, _______,
        _______, EK_____, EK_GA,   EK_CA,   EK_CG,   EK_GAS,  _______, _______, _______, _______, _______, EK_GAME,
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______, _______, _______, _______, _______, _______, _______, _______
    )
};


// Checks if a given keycode is on the modifier layers
bool isModifierLayerKey(uint16_t keycode)
{
    for (size_t i = 0; i < specialModifiersCount; i++)
    {
        if (specialModifiers[i] == keycode)
        {
            return true;
        }
    }
    return false;
}


// Tracking for modifier layers
bool isModFresh = false;
bool isGameLayerActive = false;


// Handles additional functionality for modifier layer activation keys
bool ShiftModifierLayerKey(uint16_t shiftKeycode, uint16_t modifierLayer, bool pressed)
{
    if (pressed)
    {
        register_code(shiftKeycode);
        isModFresh = true;
        layer_off(_GAME);
        return true;
    }
    if (isModFresh || IS_LAYER_OFF(modifierLayer))
    {
        unregister_code(shiftKeycode);
    }
    if (isGameLayerActive)
    {
        layer_on(_GAME);
    }
    isModFresh = false;
    return true;
}


// Some real magic
bool process_record_user(uint16_t keycode, keyrecord_t *record)
{
    bool pressed = record->event.pressed;
    // Handle layer activation keys
    switch (keycode)
    {
        case EK_GAME:
            if (pressed)
            {
                isGameLayerActive = true;
            }
            break;
        case EK_GOFF:
            if (pressed)
            {
                isGameLayerActive = false;
            }
            break;
        case EK_LMOD:
            return ShiftModifierLayerKey(KC_LSFT, _LMOD, pressed);
        case EK_RMOD:
            return ShiftModifierLayerKey(KC_RSFT, _RMOD, pressed);
        case EK_SYM:
        case EK_NAV:
            return true;
    }
    // Handle keys on the special modifier layers
    if (isModifierLayerKey(keycode) && pressed)
    {
        if (!isModFresh)
        {
            return true;
        }
        if (IS_LAYER_ON(_LMOD))
        {
            unregister_code(KC_LSFT);
        }
        else if (IS_LAYER_ON(_RMOD))
        {
            unregister_code(KC_RSFT);
        }
        isModFresh = false;
        return true;
    }
    // At this point, the keycode isn't on the modifier layer
    if (isModFresh && pressed)
    {
        layer_off(_LMOD);
        layer_off(_RMOD);
        isModFresh = false;
    }
    return true;
}


// Make _RAT layer accessible
layer_state_t layer_state_set_user(layer_state_t state)
{
    return update_tri_layer_state(state, _SYMBOL, _NAV, _RAT);
}
