#include <math.h>
#include <zephyr/kernel.h>

#include <zephyr/logging/log.h>
LOG_MODULE_DECLARE(zmk, CONFIG_ZMK_LOG_LEVEL);

#include "../custom.h"
#include "../../widgets/util.h"
#include "../../assets/custom_fonts.h"

LV_IMG_DECLARE(gauge);
LV_IMG_DECLARE(grid);

static void draw_gauge(lv_obj_t *canvas) {
    lv_draw_image_dsc_t img_dsc;
    lv_draw_image_dsc_init(&img_dsc);

    canvas_draw_img(canvas, 16, 44 + BUFFER_OFFSET_MIDDLE, &gauge, &img_dsc);
}

static void draw_needle(lv_obj_t *canvas, const uint8_t *wpm) {
    lv_draw_line_dsc_t line_dsc;
    init_line_dsc(&line_dsc, LVGL_FOREGROUND, 1);

    int centerX = 33;
    int centerY = 67 + BUFFER_OFFSET_MIDDLE;
    int offset = 13;
    int value = wpm[9];

#if IS_ENABLED(CONFIG_NICE_VIEW_GEM_WPM_FIXED_RANGE)
    float max = CONFIG_NICE_VIEW_GEM_WPM_FIXED_RANGE_MAX;
#else
    float max = 0;
    for (int i = 0; i < 10; i++) {
        if (wpm[i] > max) {
            max = wpm[i];
        }
    }
#endif
    if (max == 0)
        max = 100;
    if (value < 0)
        value = 0;
    if (value > max)
        value = max;

    float radius = 25.45585;
    float angleDeg = 225 + ((float)value / max) * 90;
    float angleRad = angleDeg * (3.14159 / 180.0f);

    int needleStartX = centerX + (int)(offset * cos(angleRad));
    int needleStartY = centerY + (int)(offset * sin(angleRad));
    int needleEndX = centerX + (int)(radius * cos(angleRad));
    int needleEndY = centerY + (int)(radius * sin(angleRad));

    lv_point_t points[2] = {{needleStartX, needleStartY}, {needleEndX, needleEndY}};
    canvas_draw_line(canvas, points, 2, &line_dsc);
}

static void draw_grid(lv_obj_t *canvas) {
    lv_draw_image_dsc_t img_dsc;
    lv_draw_image_dsc_init(&img_dsc);

    canvas_draw_img(canvas, 0, 65 + BUFFER_OFFSET_MIDDLE, &grid, &img_dsc);
}

static void draw_graph(lv_obj_t *canvas, const uint8_t *wpm) {
    lv_draw_line_dsc_t line_dsc;
    init_line_dsc(&line_dsc, LVGL_FOREGROUND, 2);
    lv_point_t points[10];

    int baselineY = 97 + BUFFER_OFFSET_MIDDLE;

#if IS_ENABLED(CONFIG_NICE_VIEW_GEM_WPM_FIXED_RANGE)
    int max = CONFIG_NICE_VIEW_GEM_WPM_FIXED_RANGE_MAX;
    if (max == 0) {
        max = 100;
    }

    int value = 0;
    for (int i = 0; i < 10; i++) {
        value = wpm[i];
        if (value > max) {
            value = max;
        }
        points[i].x = 0 + i * 7.4;
        points[i].y = baselineY - (value * 32 / max);
    }
#else
    int max = 0;
    int min = 256;

    for (int i = 0; i < 10; i++) {
        if (wpm[i] > max) {
            max = wpm[i];
        }
        if (wpm[i] < min) {
            min = wpm[i];
        }
    }

    int range = max - min;
    if (range == 0) {
        range = 1;
    }

    for (int i = 0; i < 10; i++) {
        points[i].x = 0 + i * 7.4;
        points[i].y = baselineY - (wpm[i] - min) * 32 / range;
    }
#endif

    canvas_draw_line(canvas, points, 10, &line_dsc);
}

static void draw_label(lv_obj_t *canvas, const uint8_t *wpm) {
    lv_draw_label_dsc_t label_left_dsc;
    init_label_dsc(&label_left_dsc, LVGL_FOREGROUND, &pixel_operator_mono, LV_TEXT_ALIGN_LEFT);
    canvas_draw_text(canvas, 0, 101 + BUFFER_OFFSET_MIDDLE, 25, &label_left_dsc, "WPM");

    lv_draw_label_dsc_t label_dsc_wpm;
    init_label_dsc(&label_dsc_wpm, LVGL_FOREGROUND, &pixel_operator_mono, LV_TEXT_ALIGN_RIGHT);

    char wpm_text[6] = {};

    snprintf(wpm_text, sizeof(wpm_text), "%d", wpm[9]);
    canvas_draw_text(canvas, 26, 101 + BUFFER_OFFSET_MIDDLE, 42, &label_dsc_wpm, wpm_text);
}

void custom_central_draw(lv_obj_t *canvas, const struct status_state *state) {
    draw_gauge(canvas);
    draw_needle(canvas, state->wpm);
    draw_grid(canvas);
    draw_graph(canvas, state->wpm);
    draw_label(canvas, state->wpm);
}
