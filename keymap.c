
/* Copyright 2021 Dane Evans
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
// SOFLE RGB
#include "oled.c"
#include <stdio.h>

#include QMK_KEYBOARD_H

#define INDICATOR_BRIGHTNESS 30

#define HSV_OVERRIDE_HELP(h, s, v, Override) h, s, Override
#define HSV_OVERRIDE(hsv, Override) HSV_OVERRIDE_HELP(hsv, Override)

// Light combinations
#define SET_INDICATORS(hsv) \
    {0, 1, HSV_OVERRIDE_HELP(hsv, INDICATOR_BRIGHTNESS)}, { 35 + 0, 1, hsv }
#define SET_UNDERGLOW(hsv) \
    {1, 6, hsv}, { 35 + 1, 6, hsv }
#define SET_NUMPAD(hsv) \
    {35 + 15, 5, hsv}, {35 + 22, 3, hsv}, { 35 + 27, 3, hsv }
#define SET_NUMROW(hsv) \
    {10, 2, hsv}, {20, 2, hsv}, {30, 2, hsv}, {35 + 10, 2, hsv}, {35 + 20, 2, hsv}, { 35 + 30, 2, hsv }
#define SET_INNER_COL(hsv) \
    {33, 4, hsv}, { 35 + 33, 4, hsv }

#define SET_OUTER_COL(hsv) \
    {7, 4, hsv}, { 35 + 7, 4, hsv }
#define SET_THUMB_CLUSTER(hsv) \
    {25, 2, hsv}, { 35 + 25, 2, hsv }
#define SET_LAYER_ID(hsv) \
    {0, 1, HSV_OVERRIDE_HELP(hsv, INDICATOR_BRIGHTNESS)}, {35 + 0, 1, HSV_OVERRIDE_HELP(hsv, INDICATOR_BRIGHTNESS)}, {1, 6, hsv}, {35 + 1, 6, hsv}, {7, 4, hsv}, {35 + 7, 4, hsv}, {25, 2, hsv}, { 35 + 25, 2, hsv }

#define WINDOWS_RESIZE_LEFT S(A(LWIN(SWIN(KC_F16))))

enum custom_keycodes { KC_QWERTY = SAFE_RANGE,
                       KC_COLEMAK,
                       KC_COLEMAKDH,
                       KC_LOWER,
                       KC_RAISE,
                       KC_ADJUST,
                       KC_D_MUTE };

// const key_override_t mouse_click_on_h = ko_make_basic(MOD_MASK_SHIFT, KC_DLR, KC_MS_BTN1);
// const key_override_t mouse_click_on_2_h = ko_make_basic(MOD_MASK_SHIFT, KC_UNDS, KC_MS_BTN2);
// const key_override_t mouse_click_on_3_h = ko_make_basic(MOD_MASK_SHIFT, KC_LT, KC_MS_BTN3);

// // This globally defines all key overrides to be used
// const key_override_t **key_overrides = (const key_override_t *[]){
//     &mouse_click_on_h,
//     &mouse_click_on_2_h,
//     &mouse_click_on_3_h,
//     NULL // Null terminate the array of overrides!
// };

// to update the ASCII images, run keymapviz -r keymap.c

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/* ,-----------------------------------------.                    ,-----------------------------------------.
 * | ESC  |  1   |  2   |  3   |  4   |  5   |                    |  6   |  7   |  8   |  9   |  0   | BSPC |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * | TAB  |  Q   |  W   |  E   |  R   |  T   |                    |  Y   |  U   |  I   |  O   |  P   | MINS |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * | GRV  |  A   |  S   |  D   |  F   |  G   |,------.    ,------.|  H   |  J   |  K   |  L   | SCLN | QUOT |
 * |------+------+------+------+------+------||TG(_MO|    |TG(_MO||------+------+------+------+------+------|
 * | LSFT |  Z   |  X   |  C   |  V   |  B   |`------'    `------'|  N   |  M   | COMM | DOT  | SLSH | RSFT |
 * `-------------+------+------+------+-.------------.    ,------------.-+------+------+------+-------------'
 *               | LCTL | LALT | LGUI |/MO(_SY/ ENT  /    \ SPC  \MO(_MO\| RGUI | RALT | LCTL |
 *               |      |      |      /      /      /      \      \      \      |      |      |
 *               `---------------------------------'        `---------------------------------'
 *                                                                                   generated by [keymapviz] */
    // clang-format off

    [_QWERTY] = LAYOUT(KC_ESC, KC_1, KC_2, KC_3, KC_4, KC_5, 
    KC_6, KC_7, KC_8, KC_9, KC_0, KC_BSPC, 
    
    KC_TAB, KC_Q, KC_W, KC_E, KC_R, KC_T, 
    KC_Y, KC_U, KC_I, KC_O, KC_P, KC_MINS,
    
    KC_GRV, KC_A, KC_S, KC_D, KC_F, KC_G, 
    KC_H, KC_J, KC_K, KC_L, KC_SCLN, KC_QUOT, 
    
    KC_LSFT, KC_Z, KC_X, KC_C, KC_V, KC_B, TG(_MOUSE), 
    TG(_MOUSE), KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH, KC_RSFT, 

    KC_LCTL, KC_LALT, KC_LGUI, MO(_SYMBOLS), KC_ENT, 
    KC_SPC, MO(_MOVE), KC_RGUI, KC_RALT, MO(_MOUSE)),




/* ,-----------------------------------------.                    ,-----------------------------------------.
 * |RGB_TO|  1   |  2   |  3   |  4   |  5   |                    |  6   |  7   |  8   |  9   |  0   | GRV  |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * | ESC  |  Q   |  W   |  F   |  P   |MS_WH_|                    |MS_BTN|MS_BTN|MS_BTN|MS_BTN| SCLN | BSPC |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * | TAB  |  A   |  R   |  S   |  T   |MS_WH_|,------.    ,------.|MS_BTN|MS_BTN|MS_BTN|  I   |  O   | QUOT |
 * |------+------+------+------+------+------||MS_BTN|    |TG(_MO||------+------+------+------+------+------|
 * |      |  Z   |  X   |  C   |  D   |  V   |`------'    `------'|  K   |  H   | COMM | DOT  | SLSH | RSFT |
 * `-------------+------+------+------+-.------------.    ,------------.-+------+------+------+-------------'
 *               | LGUI | LALT | LCTL |/TG(_MO/ ENT  /    \ SPC  \TG(_MO\| RCTL | RALT | RGUI |
 *               |      |      |      /      /      /      \      \      \      |      |      |
 *               `---------------------------------'        `---------------------------------'
 *                                                                                   generated by [keymapviz] */

    // clang-format off
    [_MOUSE] = LAYOUT(RGB_TOG, KC_1, KC_2, KC_3, KC_4, KC_5, 
    KC_6, KC_7, KC_8, KC_9, KC_0, KC_GRV, 
    
    KC_ESC, KC_Q, KC_W, KC_F, KC_P, KC_MS_WH_UP, 
    KC_MS_BTN1, KC_MS_BTN2, KC_MS_BTN3, KC_MS_BTN4, KC_SCLN, KC_BSPC, 
    
    KC_TAB, KC_A, KC_R, KC_S, KC_T, KC_MS_WH_DOWN, 
    KC_MS_BTN1, KC_MS_BTN2, KC_MS_BTN3, KC_I, KC_O, KC_QUOT, 
    
    KC_TRNS, KC_Z, KC_X, KC_C, KC_D, KC_V, KC_MS_BTN1, 
    TG(_MOUSE), KC_K, KC_H, KC_COMM, KC_DOT, KC_SLSH, KC_RSFT, 
    
    KC_LGUI, KC_LALT, KC_LCTL, TG(_MOUSE), KC_ENT, 
    KC_SPC, TG(_MOUSE), KC_RCTL, KC_RALT, KC_RGUI),





/* ,-----------------------------------------.                    ,-----------------------------------------.
 * |TILDE |  F1  |  F2  |  F3  |  F4  |  F5  |                    |  F6  |  F7  |  F8  |  F9  | F10  | F11  |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      |  1   | EXLM | QUOT | LPRN | RPRN |                    | MINS | EQL  |  GT  |SWIN(K|SWIN(K| F12  |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      | EXLM | QUES | DQUO | LBRC | RBRC |,------.    ,------.| DLR  | UNDS |  LT  | LPRN | RPRN | PIPE |
 * |------+------+------+------+------+------||      |    |      ||------+------+------+------+------+------|
 * |      | EQL  | DOT  | PLUS | LCBR | RCBR |`------'    `------'| SCLN | PIPE | BSLS | COLN | BSLS | LSFT |
 * `-------------+------+------+------+-.------------.    ,------------.-+------+------+------+-------------'
 *               |MO(_MO| LALT | LGUI |/      /      /    \ BSPC \ LSFT \| RGUI | RALT | LCTL |
 *               |      |      |      /      /      /      \      \      \      |      |      |
 *               `---------------------------------'        `---------------------------------'
 *                                                                                   generated by [keymapviz] */
    
    // clang-format off
    [_SYMBOLS] = LAYOUT(KC_TILDE, KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, 
    KC_F6, KC_F7, KC_F8, KC_F9, KC_F10, KC_F11, 
    
    KC_TRNS, KC_1, KC_EXLM, KC_QUOT, KC_LPRN, KC_RPRN, 
    KC_MINS, KC_EQL, KC_GT, SWIN(KC_LBRC), SWIN(KC_RBRC), KC_F12, 
    
    KC_TRNS, KC_EXLM, KC_QUES, KC_DQUO, KC_LBRC, KC_RBRC, 
    KC_DLR, KC_UNDS, KC_LT, KC_LPRN, KC_RPRN, KC_PIPE, 
    
    KC_TRNS, KC_EQL, KC_DOT, KC_PLUS, KC_LCBR, KC_RCBR, KC_TRNS, 
    KC_TRNS, KC_SCLN, KC_PIPE, KC_BSLS, KC_COLN, KC_BSLS, KC_LSFT, 
    
    MO(_MOUSE), KC_LALT, KC_LGUI, KC_TRNS, KC_TRNS, 
    KC_BSPC, KC_LSFT, KC_RGUI, KC_RALT, KC_LCTL),




/* ,-----------------------------------------.                    ,-----------------------------------------.
 * | GRV  | EQL  | MINS | LBRC | RBRC |      |                    | BSLS | SLSH |      |      |      | DEL  |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      |LWIN(K|  UP  |LWIN(K|A(KC_R| PGUP |                    | PGUP |      |S(A(LW|S(A(LW|S(A(LW| BSPC |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      | LEFT | DOWN | RGHT |A(KC_L| PGDN |,------.    ,------.| PGDN |WINDOW|S(A(LW|S(A(LW| DEL  | BSPC |
 * |------+------+------+------+------+------|| MUTE |    |      ||------+------+------+------+------+------|
 * | LSFT |LWIN(K|LWIN(K|LWIN(K|LWIN(K|      |`------'    `------'|      |S(A(LW|S(A(LW|      |      |      |
 * `-------------+------+------+------+-.------------.    ,------------.-+------+------+------+-------------'
 *               |      |      |      |/ LSFT / BSPC /    \      \      \|      |      |      |
 *               |      |      |      /      /      /      \      \      \      |      |      |
 *               `---------------------------------'        `---------------------------------'
 *                                                                                   generated by [keymapviz] */
    
    // clang-format off
    [_MOVE] = LAYOUT(KC_GRV, KC_EQL, KC_MINS, KC_LBRC, KC_RBRC, KC_TRNS, 
    KC_BSLS, KC_SLSH, KC_TRNS, KC_TRNS, KC_TRNS, KC_DEL, 
    
    KC_TRNS, LWIN(KC_LEFT), KC_UP, LWIN(KC_RGHT), A(KC_RGHT), KC_PGUP, 
    KC_PGUP, KC_TRNS, S(A(LWIN(SWIN(KC_F20)))), S(A(LWIN(SWIN(KC_F19)))), S(A(LWIN(SWIN(KC_F18)))), KC_BSPC, 
    
    KC_TRNS, KC_LEFT, KC_DOWN, KC_RGHT, A(KC_LEFT), KC_PGDN, 
    KC_PGDN, WINDOWS_RESIZE_LEFT, S(A(LWIN(SWIN(KC_F17)))), S(A(LWIN(SWIN(KC_F15)))), KC_DEL, KC_BSPC, 
    
    KC_LSFT, LWIN(KC_Z), LWIN(KC_X), LWIN(KC_C), LWIN(KC_V), KC_NO, KC_MUTE, 
    KC_TRNS, KC_NO, S(A(LWIN(SWIN(KC_M)))), S(A(LWIN(SWIN(KC_M)))), KC_TRNS, KC_NO, KC_TRNS, KC_TRNS, 

    KC_TRNS, KC_TRNS, KC_LSFT, KC_BSPC, 
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS)

};

#ifdef RGBLIGHT_ENABLE
// char layer_state_str[70];
// // Now define the array of layers. Later layers take precedence

// // QWERTY,
// // Light on inner column and underglow
// const rgblight_segment_t PROGMEM layer_qwerty_lights[]    = RGBLIGHT_LAYER_SEGMENTS(SET_LAYER_ID(HSV_RED)

//    );
// const rgblight_segment_t PROGMEM layer_colemakdh_lights[] = RGBLIGHT_LAYER_SEGMENTS(SET_LAYER_ID(HSV_PINK));

// // _NUM,
// // Light on outer column and underglow
// const rgblight_segment_t PROGMEM layer_num_lights[] = RGBLIGHT_LAYER_SEGMENTS(SET_LAYER_ID(HSV_TEAL)

// );
// // _SYMBOL,
// // Light on inner column and underglow
// const rgblight_segment_t PROGMEM layer_symbol_lights[] = RGBLIGHT_LAYER_SEGMENTS(SET_LAYER_ID(HSV_BLUE)

// );
// // _COMMAND,
// // Light on inner column and underglow
// const rgblight_segment_t PROGMEM layer_command_lights[] = RGBLIGHT_LAYER_SEGMENTS(SET_LAYER_ID(HSV_PURPLE));

// //_NUMPAD
// const rgblight_segment_t PROGMEM layer_numpad_lights[] = RGBLIGHT_LAYER_SEGMENTS(SET_INDICATORS(HSV_ORANGE), SET_UNDERGLOW(HSV_ORANGE), SET_NUMPAD(HSV_BLUE), {7, 4, HSV_ORANGE}, {25, 2, HSV_ORANGE}, {35 + 6, 4, HSV_ORANGE}, {35 + 25, 2, HSV_ORANGE});
// // _SWITCHER   // light up top row
// const rgblight_segment_t PROGMEM layer_switcher_lights[] = RGBLIGHT_LAYER_SEGMENTS(SET_LAYER_ID(HSV_GREEN), SET_NUMROW(HSV_GREEN));

// const rgblight_segment_t* const PROGMEM my_rgb_layers[] = RGBLIGHT_LAYERS_LIST(

//     layer_qwerty_lights,
//     layer_num_lights, // overrides layer 1
//     layer_symbol_lights, layer_command_lights, layer_numpad_lights,
//     layer_switcher_lights, // Overrides other layers
//     layer_colemakdh_lights);

// layer_state_t layer_state_set_user(layer_state_t state) {
//     rgblight_set_layer_state(0, layer_state_cmp(state, _DEFAULTS) && layer_state_cmp(default_layer_state, _QWERTY));
//     rgblight_set_layer_state(7, layer_state_cmp(state, _DEFAULTS) && layer_state_cmp(default_layer_state, _MOUSE));

//     rgblight_set_layer_state(1, layer_state_cmp(state, _MOUSE));
//     rgblight_set_layer_state(2, layer_state_cmp(state, _SYMBOLS));
//     rgblight_set_layer_state(3, layer_state_cmp(state, _MOVE));
//     return state;
// }
// void keyboard_post_init_user(void) {
//     // Enable the LED layers
//     rgblight_layers = my_rgb_layers;

//     rgblight_mode(10); // haven't found a way to set this in a more useful way

//     pimoroni_trackball_set_rgbw(0, 0, 254, 0);
// }
#endif

bool process_record_user(uint16_t keycode, keyrecord_t* record) {
    
    switch (keycode) {
        case KC_QWERTY:
            if (record->event.pressed) {
                set_single_persistent_default_layer(_QWERTY);
            }
            return false;
        case KC_COLEMAK:
            if (record->event.pressed) {
                set_single_persistent_default_layer(_MOUSE);
            }
            return false;
        case KC_COLEMAKDH:
            if (record->event.pressed) {
                set_single_persistent_default_layer(_MOUSE);
            }
            return false;
        case KC_LOWER:
            if (record->event.pressed) {
                layer_on(_MOUSE);
                update_tri_layer(_MOUSE, _SYMBOLS, _MOVE);
            } else {
                layer_off(_MOUSE);
                update_tri_layer(_MOUSE, _SYMBOLS, _MOVE);
            }
            return false;
        case KC_RAISE:
            if (record->event.pressed) {
                layer_on(_SYMBOLS);
                update_tri_layer(_MOUSE, _SYMBOLS, _MOVE);
            } else {
                layer_off(_SYMBOLS);
                update_tri_layer(_MOUSE, _SYMBOLS, _MOVE);
            }
            return false;
        case KC_ADJUST:
            if (record->event.pressed) {
                layer_on(_MOVE);
            } else {
                layer_off(_MOVE);
            }
            return false;
        case KC_D_MUTE:
            if (record->event.pressed) {
                register_mods(mod_config(MOD_MEH));
                register_code(KC_UP);
            } else {
                unregister_mods(mod_config(MOD_MEH));
                unregister_code(KC_UP);
            }
    }
    return true;
}

#ifdef ENCODER_ENABLE

bool encoder_update_user(uint8_t index, bool clockwise) {
    switch (get_highest_layer(layer_state)) {
        case _MOUSE:
            if (clockwise) {
                tap_code(KC_PGDN);
            } else {
                tap_code(KC_PGUP);
            }
            break;
        case _MOVE:
            if (clockwise) {
                tap_code(KC_VOLU);
            } else {
                tap_code(KC_VOLD);
            }
            break;
        default:
            if (clockwise) {
                tap_code(KC_WH_D);
            } else {
                tap_code(KC_WH_U);
            }
            break;
    }

    return true;
}

#endif
