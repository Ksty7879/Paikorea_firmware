// Copyright 2026 Ksty7879
// SPDX-License-Identifier: MIT
#include "paikorea.h"

#ifdef POINTING_DEVICE_ENABLE

#    ifndef PAIKOREA_SCROLL_DIVISOR
#        define PAIKOREA_SCROLL_DIVISOR 8
#    endif

static bool    drag_scroll_held = false;
static bool    pads_swapped     = false;
static int16_t scroll_acc_h[2]  = {0, 0};
static int16_t scroll_acc_v[2]  = {0, 0};

/* Turn cursor motion of one pad into wheel motion. Buttons (taps) and the
 * pad's own two-finger scroll are kept as they are. */
static report_mouse_t paikorea_to_scroll(report_mouse_t report, uint8_t side) {
    scroll_acc_h[side] += report.x;
    scroll_acc_v[side] += report.y;

    int16_t h = scroll_acc_h[side] / PAIKOREA_SCROLL_DIVISOR;
    int16_t v = scroll_acc_v[side] / PAIKOREA_SCROLL_DIVISOR;
    scroll_acc_h[side] -= h * PAIKOREA_SCROLL_DIVISOR;
    scroll_acc_v[side] -= v * PAIKOREA_SCROLL_DIVISOR;

#    ifdef PAIKOREA_SCROLL_INVERT
    v = -v;
    h = -h;
#    endif
    report.h += h;
    report.v -= v; // finger up -> wheel up
    report.x = 0;
    report.y = 0;
    return report;
}

report_mouse_t pointing_device_task_combined_kb(report_mouse_t left_report, report_mouse_t right_report) {
    bool left_scrolls  = drag_scroll_held || !pads_swapped;
    bool right_scrolls = drag_scroll_held || pads_swapped;

    if (left_scrolls) {
        left_report = paikorea_to_scroll(left_report, 0);
    }
    if (right_scrolls) {
        right_report = paikorea_to_scroll(right_report, 1);
    }
    return pointing_device_task_combined_user(left_report, right_report);
}

#endif // POINTING_DEVICE_ENABLE

bool process_record_kb(uint16_t keycode, keyrecord_t *record) {
    if (!process_record_user(keycode, record)) {
        return false;
    }
#ifdef POINTING_DEVICE_ENABLE
    switch (keycode) {
        case DRG_SCRL:
            drag_scroll_held = record->event.pressed;
            return false;
        case PAD_SWAP:
            if (record->event.pressed) {
                pads_swapped = !pads_swapped;
            }
            return false;
    }
#endif
    return true;
}
