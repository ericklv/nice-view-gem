/*******************************************************************************
 * Size: 11 px digits
 * Bpp: 1
 * Hand-drawn larger digits in the style of Pixel Operator Mono, used for the
 * battery percentage. Contains only " ", "%" and "0"-"9". Same 8 px advance as
 * pixel_operator_mono so the text width does not change.
 ******************************************************************************/

#ifdef LV_LVGL_H_INCLUDE_SIMPLE
#include "lvgl.h"
#else
#include <lvgl.h>
#endif

#ifndef PIXEL_OPERATOR_MONO_LARGE
#define PIXEL_OPERATOR_MONO_LARGE 1
#endif

#if PIXEL_OPERATOR_MONO_LARGE

/*-----------------
 *    BITMAPS
 *----------------*/

/*Store the image of the glyphs*/
static LV_ATTRIBUTE_LARGE_CONST const uint8_t glyph_bitmap[] = {
    /* U+0020 " " */
    0x0,

    /* U+0025 "%" */
    0x41, 0x42, 0x8a, 0x20, 0x82, 0x8, 0x24, 0x94, 0x28, 0x20,

    /* U+0030 "0" */
    0x7a, 0x18, 0x61, 0x8e, 0x5a, 0x71, 0x86, 0x17, 0x80,

    /* U+0031 "1" */
    0x23, 0x28, 0x42, 0x10, 0x84, 0x21, 0x3e,

    /* U+0032 "2" */
    0x7a, 0x10, 0x41, 0x8, 0x42, 0x10, 0x82, 0xf, 0xc0,

    /* U+0033 "3" */
    0x7a, 0x10, 0x41, 0x4, 0xe0, 0x41, 0x6, 0x17, 0x80,

    /* U+0034 "4" */
    0x4, 0x31, 0x49, 0x46, 0x1f, 0xc1, 0x4, 0x10, 0x40,

    /* U+0035 "5" */
    0xfe, 0x8, 0x20, 0xf8, 0x10, 0x41, 0x6, 0x17, 0x80,

    /* U+0036 "6" */
    0x7a, 0x18, 0x20, 0x83, 0xe8, 0x61, 0x86, 0x17, 0x80,

    /* U+0037 "7" */
    0xfc, 0x10, 0x41, 0x8, 0x42, 0x10, 0x82, 0x8, 0x0,

    /* U+0038 "8" */
    0x7a, 0x18, 0x61, 0x85, 0xe8, 0x61, 0x86, 0x17, 0x80,

    /* U+0039 "9" */
    0x7a, 0x18, 0x61, 0x85, 0xf0, 0x41, 0x6, 0x17, 0x80,
};

/*---------------------
 *  GLYPH DESCRIPTION
 *--------------------*/

static const lv_font_fmt_txt_glyph_dsc_t glyph_dsc[] = {
    {.bitmap_index = 0, .adv_w = 0, .box_w = 0, .box_h = 0, .ofs_x = 0, .ofs_y = 0} /* id = 0 reserved */,
    {.bitmap_index = 0, .adv_w = 128, .box_w = 1, .box_h = 1, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1, .adv_w = 128, .box_w = 7, .box_h = 11, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 11, .adv_w = 128, .box_w = 6, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 20, .adv_w = 128, .box_w = 5, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 27, .adv_w = 128, .box_w = 6, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 36, .adv_w = 128, .box_w = 6, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 45, .adv_w = 128, .box_w = 6, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 54, .adv_w = 128, .box_w = 6, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 63, .adv_w = 128, .box_w = 6, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 72, .adv_w = 128, .box_w = 6, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 81, .adv_w = 128, .box_w = 6, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 90, .adv_w = 128, .box_w = 6, .box_h = 11, .ofs_x = 1, .ofs_y = 0}};

/*---------------------
 *  CHARACTER MAPPING
 *--------------------*/

static const uint16_t unicode_list_0[] = {0x0, 0x5, 0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17, 0x18, 0x19};

/*Collect the unicode lists and glyph_id offsets*/
static const lv_font_fmt_txt_cmap_t cmaps[] = {{.range_start = 32,
                                                .range_length = 26,
                                                .glyph_id_start = 1,
                                                .unicode_list = unicode_list_0,
                                                .glyph_id_ofs_list = NULL,
                                                .list_length = 12,
                                                .type = LV_FONT_FMT_TXT_CMAP_SPARSE_TINY}};

/*--------------------
 *  ALL CUSTOM DATA
 *--------------------*/

#if LVGL_VERSION_MAJOR == 8
/*Store all the custom data of the font*/
static lv_font_fmt_txt_glyph_cache_t cache;
#endif

#if LVGL_VERSION_MAJOR >= 8
static const lv_font_fmt_txt_dsc_t font_dsc = {
#else
static lv_font_fmt_txt_dsc_t font_dsc = {
#endif
    .glyph_bitmap = glyph_bitmap,
    .glyph_dsc = glyph_dsc,
    .cmaps = cmaps,
    .kern_dsc = NULL,
    .kern_scale = 0,
    .cmap_num = 1,
    .bpp = 1,
    .kern_classes = 0,
    .bitmap_format = 0,
#if LVGL_VERSION_MAJOR == 8
    .cache = &cache
#endif
};

/*-----------------
 *  PUBLIC FONT
 *----------------*/

/*Initialize a public general font descriptor*/
#if LVGL_VERSION_MAJOR >= 8
const lv_font_t pixel_operator_mono_large = {
#else
lv_font_t pixel_operator_mono_large = {
#endif
    .get_glyph_dsc = lv_font_get_glyph_dsc_fmt_txt, /*Function pointer to get glyph's data*/
    .get_glyph_bitmap = lv_font_get_bitmap_fmt_txt, /*Function pointer to get glyph's bitmap*/
    .line_height = 13,                              /*The maximum line height required by the font*/
    .base_line = 2, /*Baseline measured from the bottom of the line*/
#if !(LVGL_VERSION_MAJOR == 6 && LVGL_VERSION_MINOR == 0)
    .subpx = LV_FONT_SUBPX_NONE,
#endif
#if LV_VERSION_CHECK(7, 4, 0) || LVGL_VERSION_MAJOR >= 8
    .underline_position = -3,
    .underline_thickness = 1,
#endif
    .dsc = &font_dsc, /*The custom font data. Will be accessed by `get_glyph_bitmap/dsc` */
#if LV_VERSION_CHECK(8, 2, 0) || LVGL_VERSION_MAJOR >= 9
    .fallback = NULL,
#endif
    .user_data = NULL,
};

#endif /*#if PIXEL_OPERATOR_MONO_LARGE*/
