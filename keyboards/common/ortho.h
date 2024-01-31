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
    EK_____
};


// Calculate the keycode count of the tuple
size_t specialModifiersCount = sizeof(specialModifiers) / sizeof(specialModifiers[0]);


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
        if (IS_LAYER_ON(_RMOD))
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
