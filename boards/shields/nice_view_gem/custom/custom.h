#pragma once

#include <lvgl.h>
#include "../widgets/util.h"

/**
 * Swappable art slots.
 *
 * custom/central/     central half: middle area of the status screen (rows 44-111)
 * custom/peripheral/  peripheral half: everything below the SIG/BAT rows
 *
 * The screens own all the data (battery, layer, WPM, ...) and keep it in
 * `struct status_state` (see widgets/util.h). The art only reads that state,
 * so it never subscribes to ZMK events itself.
 *
 * Every .c file in each folder is compiled automatically, and each folder may
 * add its own options in a Kconfig.defconfig. To swap the art, replace the
 * folder contents with files that implement the functions below.
 */

/**
 * Draw the middle area. Called whenever data shown there changes (currently
 * every WPM update). The canvas is already cleared and gets rotated after this
 * returns. Use absolute screen rows plus BUFFER_OFFSET_MIDDLE for y, like the
 * other widgets do.
 */
void custom_central_draw(lv_obj_t *canvas, const struct status_state *state);

/**
 * Called once when the peripheral screen is created. Add the art as children
 * of `parent` (the 160x68 screen object).
 */
void custom_peripheral_init(lv_obj_t *parent);

/**
 * Called whenever the peripheral state changes (battery, connection). Leave it
 * empty if the art doesn't react to state.
 */
void custom_peripheral_update(const struct status_state *state);
