/* Copyright 2020 Josef Adamcik
 * Modification for VIA support and RGB underglow by Jens Bonk-Wiltfang
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

#include QMK_KEYBOARD_H

#include "oled.c"
#include "encoder.c"
#include "lib/lib8tion/lib8tion.h"
#include <string.h>

// // Base layer is the number of layers CYCLE selects from.
// #define BASE_LAYERS 2

// enum custom_keycodes {
//     PLACEHOLDER = SAFE_RANGE, // can always be here (4 bytes)
//     CYCLE                     // cycle through first BASE_LAYERS (62 bytes)

// };

enum custom_layers { _QWERTY, _MOUSE, _SYMBOLS, _MOVE };

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    [_QWERTY] = LAYOUT(KC_ESC, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, KC_BSPC, KC_TAB, KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P, KC_MINS, KC_GRV, KC_A, KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K, KC_L, KC_SCLN, KC_QUOT, KC_LSFT, KC_Z, KC_X, KC_C, KC_V, KC_B, TG(1), TG(1), KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH, KC_RSFT, KC_LCTL, KC_LALT, KC_LGUI, MO(2), KC_ENT, KC_SPC, MO(3), KC_RGUI, KC_RALT, KC_LCTL),

    [_MOUSE] = LAYOUT(RGB_TOG, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, KC_GRV, KC_ESC, KC_Q, KC_W, KC_F, KC_P, KC_MS_WH_UP, KC_MS_BTN1, KC_MS_BTN2, KC_MS_BTN3, KC_MS_BTN4, KC_SCLN, KC_BSPC, KC_TAB, KC_A, KC_R, KC_S, KC_T, KC_MS_WH_DOWN, KC_M, KC_N, KC_E, KC_I, KC_O, KC_QUOT, KC_LSFT, KC_Z, KC_X, KC_C, KC_D, KC_V, KC_MS_BTN1, TG(1), KC_K, KC_H, KC_COMM, KC_DOT, KC_SLSH, KC_RSFT, KC_LGUI, KC_LALT, KC_LCTL, TG(1), KC_ENT, KC_SPC, TG(1), KC_RCTL, KC_RALT, KC_RGUI),

    [_SYMBOLS] = LAYOUT(KC_TILDE, KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6, KC_F7, KC_F8, KC_F9, KC_F10, KC_F11, KC_GRV, KC_1, KC_EXLM, KC_QUOT, KC_LPRN, KC_RPRN, KC_MINS, KC_EQL, KC_GT, SWIN(KC_LBRC), SWIN(KC_RBRC), KC_F12, KC_TRNS, KC_EXLM, KC_QUES, KC_DQUO, KC_LBRC, KC_RBRC, KC_DLR, KC_UNDS, KC_LT, KC_LPRN, KC_RPRN, KC_PIPE, KC_LSFT, KC_EQL, KC_DOT, KC_PLUS, KC_LCBR, KC_RCBR, KC_TRNS, KC_TRNS, KC_SCLN, KC_PIPE, KC_BSLS, KC_COLN, KC_BSLS, KC_LSFT, KC_LCTL, KC_LALT, KC_LGUI, KC_TRNS, KC_TRNS, KC_BSPC, KC_LSFT, KC_RGUI, KC_RALT, KC_LCTL),

    [_MOVE] = LAYOUT(KC_GRV, KC_EQL, KC_MINS, KC_LBRC, KC_RBRC, KC_TRNS, KC_BSLS, KC_SLSH, KC_TRNS, KC_TRNS, KC_TRNS, KC_DEL, KC_TRNS, LWIN(KC_LEFT), KC_UP, LWIN(KC_RGHT), A(KC_RGHT), KC_PGUP, KC_PGUP, KC_TRNS, S(A(LWIN(SWIN(KC_F20)))), S(A(LWIN(SWIN(KC_F19)))), S(A(LWIN(SWIN(KC_F18)))), KC_BSPC, KC_TRNS, KC_LEFT, KC_DOWN, KC_RGHT, A(KC_LEFT), KC_PGDN, KC_PGDN, S(A(LWIN(SWIN(KC_F16)))), S(A(LWIN(SWIN(KC_F17)))), S(A(LWIN(SWIN(KC_F15)))), KC_DEL, KC_BSPC, KC_TRNS, LWIN(KC_Z), LWIN(KC_X), LWIN(KC_C), LWIN(KC_V), KC_NO, KC_MUTE, KC_TRNS, KC_NO, S(A(LWIN(SWIN(KC_M)))), S(A(LWIN(SWIN(KC_M)))), KC_TRNS, KC_NO, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_LSFT, KC_BSPC, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS)

};

#if defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][2] = {
    [_QWERTY]  = {ENCODER_CCW_CW(KC_MS_WH_UP, KC_MS_WH_DOWN)},
    [_MOUSE]   = {ENCODER_CCW_CW(RGB_VAD, RGB_VAI)},
    [_SYMBOLS] = {ENCODER_CCW_CW(QK_BACKLIGHT_DOWN, QK_BACKLIGHT_UP)},
    [_MOVE]    = {ENCODER_CCW_CW(KC_VOLD, KC_VOLU)},
};
#endif

// // Custom keycode handling.
// bool process_record_user(uint16_t keycode, keyrecord_t* record) {
//     // handling this once instead of in each keycode uses less program memory.
//     if ((keycode >= SAFE_RANGE) && !(record->event.pressed)) {
//         return false;
//     }

//     switch (keycode) {
//         case CYCLE:
//             set_single_persistent_default_layer((1 + get_highest_layer(default_layer_state)) % BASE_LAYERS);
//             break;
//     }

//     // this uses less memory than returning in each case.
//     return keycode < SAFE_RANGE;
// };

// uint32_t layer_state_set_user(uint32_t state) {
//     switch (get_highest_layer(state)) {
//         case _MOVE:
//             rgblight_setrgb(RGB_BLUE);
//             break;
//         case _SYMBOLS:
//             rgblight_setrgb(RGB_RED);
//             break;
//         default: // for any other layers, or the default layer
//             rgblight_setrgb(RGB_WHITE);
//             break;
//     }
//     return state;
// }

#define RBG_VAL 255
layer_state_t layer_state_set_user(layer_state_t state) {
    switch (biton32(state)) {
        case _MOUSE:
            // green-ish
            // rgblight_sethsv_noeeprom(72, 221, RBG_VAL);
            rgblight_sethsv_noeeprom(HSV_GREEN);
            break;
        case _SYMBOLS:
            // Red
            rgblight_sethsv_noeeprom(HSV_RED);
            break;
        case _MOVE:
            // Dark Blue
            rgblight_sethsv_noeeprom(HSV_BLUE);
            break;
        default:
            // Default colors
            rgblight_sethsv(HSV_CYAN);
            break;
    }
    return state;
}

// LED LIGHTS GOOD
// should be 74

// const rgblight_segment_t PROGMEM my_capslock_layer[] = RGBLIGHT_LAYER_SEGMENTS({1, 74, HSV_WHITE});
// const rgblight_segment_t PROGMEM my_layer1_layer[]   = RGBLIGHT_LAYER_SEGMENTS({1, 74, HSV_CYAN});
// const rgblight_segment_t PROGMEM my_layer2_layer[]   = RGBLIGHT_LAYER_SEGMENTS({1, 74, HSV_RED});
// const rgblight_segment_t PROGMEM my_layer3_layer[]   = RGBLIGHT_LAYER_SEGMENTS({1, 74, HSV_GREEN});
// const rgblight_segment_t PROGMEM my_mouse_layer[]    = RGBLIGHT_LAYER_SEGMENTS({1, 74, HSV_YELLOW});

// // Now define the array of layers. Later layers take precedence
// const rgblight_segment_t* const PROGMEM my_rgb_layers[] = RGBLIGHT_LAYERS_LIST(my_capslock_layer,
//                                                                                my_layer1_layer, // Overrides caps lock layer
//                                                                                my_layer2_layer, // Overrides other layers
//                                                                                my_layer3_layer, // Overrides other layers,
//                                                                                my_mouse_layer);

void keyboard_post_init_user(void) {
    // debug_enable = true;

    pimoroni_trackball_set_rgbw(0, 0, 254, 0);

    // Enable the LED layers
    // rgblight_layers = my_rgb_layers;
}

// bool led_update_user(led_t led_state) {
//     rgblight_set_layer_state(0, led_state.caps_lock);
//     return true;
// }

// layer_state_t default_layer_state_set_user(layer_state_t state) {
//     rgblight_set_layer_state(1, layer_state_cmp(state, _QWERTY));
//     return state;
// }

// layer_state_t layer_state_set_user(layer_state_t state) {
//     rgblight_set_layer_state(1, layer_state_cmp(state, _QWERTY));
//     rgblight_set_layer_state(2, layer_state_cmp(state, _MOVE));
//     rgblight_set_layer_state(3, layer_state_cmp(state, _SYMBOLS));
//     rgblight_set_layer_state(4, layer_state_cmp(state, _MOUSE));
//     return state;
// }

// PIMORONI

// static uint32_t       last_mouse_activity = 0;
// static report_mouse_t last_mouse_report   = {0};
// static bool           is_scrolling        = false;

// report_mouse_t smooth_mouse_movement(report_mouse_t mouse_report) {
//     // Linear interpolation and ease-in-out
//     static fract8 fract = 0.5;
//     int8_t        x     = 0;
//     int8_t        y     = 0;
//     int8_t        h     = 0;
//     int8_t        v     = 0;

//     if (!is_scrolling) {
//         x = ease8InOutApprox(lerp8by8(last_mouse_report.x, mouse_report.x, fract));
//         y = ease8InOutApprox(lerp8by8(last_mouse_report.y, mouse_report.y, fract));
//     } else {
//         h = ease8InOutApprox(lerp8by8(last_mouse_report.x, mouse_report.x, fract));
//         v = ease8InOutApprox(lerp8by8(last_mouse_report.y, mouse_report.y, fract));
//     }

//     // update the new smoothed report
//     mouse_report.x = x;
//     mouse_report.y = y;
//     mouse_report.h = h;
//     mouse_report.v = v;

//     return mouse_report;
// }

// report_mouse_t pointing_device_task_user(report_mouse_t mouse_report) {
//     if (has_mouse_report_changed(&last_mouse_report, &mouse_report)) {
//         last_mouse_activity = timer_read32();
//         memcpy(&last_mouse_report, &mouse_report, sizeof(mouse_report));
//     }

//     return smooth_mouse_movement(mouse_report);
// }
