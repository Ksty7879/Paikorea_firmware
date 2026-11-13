// Copyright 2026 Ksty7879
// SPDX-License-Identifier: MIT
#pragma once

/* ---------------------------------------------------------------------------
 * Split / handedness
 *
 * Both halves are the same reversible PCB (front build = right half,
 * back build = left half), so handedness is stored in EEPROM.
 * The CI build produces a *_left.uf2 and a *_right.uf2 that write the
 * correct side on first boot (see keymaps/vial/rules.mk).
 * ------------------------------------------------------------------------- */
#define EE_HANDS
#define SPLIT_USB_DETECT
#define SPLIT_WATCHDOG_TIMEOUT 3000

/* ---------------------------------------------------------------------------
 * Trackpads: Azoteq TPS43 (IQS572) on I2C0, GP8 = SDA, GP9 = SCL
 *   - right half (front build): via the 6-pin FFC connector J2
 *   - left half  (back build) : wire SDA/SCL/3V3/GND straight to GP8/GP9
 * RDY / RST (FFC pin 5/6) are not used.
 * ------------------------------------------------------------------------- */
#define I2C_DRIVER I2CD0
#define I2C1_SDA_PIN GP8
#define I2C1_SCL_PIN GP9

#define AZOTEQ_IQS5XX_TPS43
#define AZOTEQ_IQS5XX_TAP_ENABLE true             // 1-finger tap  = left click
#define AZOTEQ_IQS5XX_TWO_FINGER_TAP_ENABLE true  // 2-finger tap  = right click
#define AZOTEQ_IQS5XX_SCROLL_ENABLE true          // 2-finger drag = scroll
#define AZOTEQ_IQS5XX_PRESS_AND_HOLD_ENABLE true  // tap-and-hold  = drag / select

/* One trackpad on each half, reports combined on the master side. */
#define SPLIT_POINTING_ENABLE
#define POINTING_DEVICE_COMBINED

/* Orientation fixes. Uncomment what you need after the first test.
 * The plain ones apply to the left pad, *_RIGHT to the right pad. */
// #define POINTING_DEVICE_ROTATION_180
// #define POINTING_DEVICE_INVERT_X
// #define POINTING_DEVICE_INVERT_Y
// #define POINTING_DEVICE_ROTATION_180_RIGHT
// #define POINTING_DEVICE_INVERT_X_RIGHT
// #define POINTING_DEVICE_INVERT_Y_RIGHT

/* Left pad = 1-finger scroll, right pad = cursor (swap with PAD_SWAP key). */
#define PAIKOREA_SCROLL_DIVISOR 8
// #define PAIKOREA_SCROLL_INVERT   // natural (touchpad-style) scrolling

/* ---------------------------------------------------------------------------
 * RP2040-Zero: double-tap the RESET button to enter the UF2 bootloader.
 * ------------------------------------------------------------------------- */
#define RP2040_BOOTLOADER_DOUBLE_TAP_RESET
#define RP2040_BOOTLOADER_DOUBLE_TAP_RESET_TIMEOUT 500U
