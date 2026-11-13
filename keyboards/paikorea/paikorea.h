// Copyright 2026 Ksty7879
// SPDX-License-Identifier: MIT
#pragma once

#include "quantum.h"

/* Keyboard-level custom keycodes.
 * Vial shows them under "User" as listed in keymaps/vial/vial.json
 * (customKeycodes are mapped to QK_KB_0, QK_KB_1, ... in order). */
enum paikorea_keycodes {
    DRG_SCRL = QK_KB_0, // hold: both trackpads scroll
    PAD_SWAP,           // tap : swap cursor/scroll roles of the two pads
};
