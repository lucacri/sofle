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

// Sets up what the OLED screens display.

// Screen is I2C SSD1306. 128 x 32

static void print_status_narrow(void) {
    // Print current layer
    oled_write_ln_P(PSTR("LAYER"), false);
    switch (get_highest_layer(layer_state)) {
        case 0: // _QWERTY
            oled_write_P(PSTR("Base\n"), false);
            break;
        case 1: // _COLEMAK
            oled_write_P(PSTR("Mouse\n"), false);
            break;
        case 2:
            oled_write_P(PSTR("Symbols"), false);
            break;
        case 3:
            oled_write_P(PSTR("Move"), false);
            break;
        default:
            oled_write_ln_P(PSTR("Undef"), false);
    }
    oled_write_P(PSTR("\n\n"), false);
    led_t led_usb_state = host_keyboard_led_state();
    oled_write_ln_P(PSTR("CPSLK"), led_usb_state.caps_lock);
    oled_write_ln_P(PSTR("Luca"),false);
}

oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    return OLED_ROTATION_270;
}

static void render_empty_logo(void) {
    oled_write_P(PSTR("\n\n\n"), false);
}
static void render_apple_logo(void) {
    static const char PROGMEM apple1[] = {0x80, 0x81, 0x82, 0x83, 0x00};
    static const char PROGMEM apple2[] = {0xA0, 0xA1, 0xA2, 0xA3, 0x00};
    static const char PROGMEM apple3[] = {0xC0, 0xC1, 0xC2, 0xC3, 0x00};
    oled_write_ln_P(apple1, false);
    oled_write_ln_P(apple2, false);
    oled_write_ln_P(apple3, false);
}
static void render_alt_logo(void) {
    static const char PROGMEM apple1[] = {0x84, 0x85, 0x86, 0x87, 0x00};
    static const char PROGMEM apple2[] = {0xA4, 0xA5, 0xA6, 0xA7, 0x00};
    static const char PROGMEM apple3[] = {0xC4, 0xC5, 0xC6, 0xC7, 0x00};
    oled_write_ln_P(apple1, false);
    oled_write_ln_P(apple2, false);
    oled_write_ln_P(apple3, false);
}

static void render_ctrl_logo(void) {
    static const char PROGMEM apple1[] = {0x88, 0x89, 0x8A, 0x8B, 0x00};
    static const char PROGMEM apple2[] = {0xA8, 0xA9, 0xAA, 0xAB, 0x00};
    static const char PROGMEM apple3[] = {0xC8, 0xC9, 0xCA, 0xCB, 0x00};
    oled_write_ln_P(apple1, false);
    oled_write_ln_P(apple2, false);
    oled_write_ln_P(apple3, false);
}

static void render_shift_logo(void) {
    // 'apple-logo', 32x32px
    static const char PROGMEM apple1[] = {0x8C, 0x8D, 0x8E, 0x8F, 0x00};
    static const char PROGMEM apple2[] = {0xAC, 0xAD, 0xAE, 0xAF, 0x00};
    static const char PROGMEM apple3[] = {0xCC, 0xCD, 0xCE, 0xCF, 0x00};
    oled_write_ln_P(apple1, false);
    oled_write_ln_P(apple2, false);
    oled_write_ln_P(apple3, false);
}

void render_mod_status(uint8_t modifiers) {
    if ((modifiers & MOD_MASK_GUI)) {
        render_apple_logo();
    } else {
        render_empty_logo();
    }

    if ((modifiers & MOD_MASK_ALT)) {
        render_alt_logo();
    } else {
        render_empty_logo();
    }

    if ((modifiers & MOD_MASK_CTRL)) {
        render_ctrl_logo();
    } else {
        render_empty_logo();
    }

    if ((modifiers & MOD_MASK_SHIFT)) {
        render_shift_logo();
    } else {
        render_empty_logo();
    }
}

bool oled_task_user(void) {
    if (is_keyboard_master()) {
        render_mod_status(get_mods());
    } else {
        print_status_narrow();

    }
    return false;
}
