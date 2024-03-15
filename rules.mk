# RGBLIGHT_ENABLE = yes

# MCU = atmega32u4
# BOOTLOADER = rp2040
# CONVERT_TO = kb2040

# Build Options
# Comment out to disable the options.

MOUSEKEY_ENABLE = yes
EXTRAKEY_ENABLE = yes
CONSOLE_ENABLE = no
RGBLIGHT_ENABLE = no
ENCODER_ENABLE = yes
ENCODER_MAP_ENABLE = no
LTO_ENABLE = yes
OLED_ENABLE = yes
OLED_DRIVER = ssd1306
VIA_ENABLE = yes 				# VIA_ENABLE with the keymap (+2300). Note: VIA is required as non-via layouts were removed to save space.
KEY_OVERRIDE_ENABLE = yes

WPM_ENABLE = yes					# WPM counter for typing-speed-reactive keyboard pets (+782)

POINTING_DEVICE_ENABLE = no
POINTING_DEVICE_DRIVER = pimoroni_trackball

SWAP_HANDS_ENABLE = no
SLEEP_LED_ENABLE = no

CONSOLE_ENABLE = no
COMMAND_ENABLE = no         # Commands for debug and configuration

NO_USB_STARTUP_CHECK = yes