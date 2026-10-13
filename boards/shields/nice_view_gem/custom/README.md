# Swappable art

| Folder        | Half       | Screen area                        | Default                |
| ------------- | ---------- | ---------------------------------- | ---------------------- |
| `central/`    | central    | middle area, rows 44–111           | WPM gauge and chart    |
| `peripheral/` | peripheral | everything below the SIG/BAT rows | floating crystal       |

The screens own all the data (battery, connection, layer, profile, WPM) and pass
it to the art as a read-only `struct status_state` (see `../widgets/util.h`). The
screens only call the functions declared in [`custom.h`](custom.h), so the art in
each folder can be replaced without touching anything else:

- Every `*.c` file in the folder is compiled automatically (see `../CMakeLists.txt`).
- An optional `Kconfig.defconfig` in the folder holds that art's own options.
  Keep the file (it may be empty) because `../Kconfig.defconfig` sources it.

## Replacing the crystal (`peripheral/`)

Implement `void custom_peripheral_init(lv_obj_t *parent)` and add your images as
children of `parent`. Also implement `void custom_peripheral_update(const struct status_state *state)`,
which is called whenever the battery or connection changes (leave it empty if
the art doesn't react to it). For a single static image:

```c
#include <zephyr/kernel.h>
#include "../custom.h"

LV_IMG_DECLARE(my_art); // defined in another .c file in this folder

void custom_peripheral_init(lv_obj_t *parent) {
    lv_obj_t *art = lv_img_create(parent);
    lv_img_set_src(art, &my_art);
    lv_obj_align(art, LV_ALIGN_TOP_LEFT, 36, 0);
}

void custom_peripheral_update(const struct status_state *state) {}
```

Images are 1-bit `LV_COLOR_FORMAT_I1`. Like the crystal frames, they are shown
unrotated, so draw them for the landscape 160x68 screen (the crystal frames are
69x68 and sit at x=36).

## Replacing the WPM (`central/`)

Implement `void custom_central_draw(lv_obj_t *canvas, const struct status_state *state)`
and draw into the middle canvas with the helpers in `../widgets/util.h`, using
y = screen row + `BUFFER_OFFSET_MIDDLE`. It is called on every WPM update.
`state->wpm` holds the last 10 samples (oldest first, `state->wpm[9]` is the
latest), so the art can use the WPM or ignore it. The WPM tracking itself stays
in `../widgets/screen.c`. For a static image:

```c
#include <zephyr/kernel.h>
#include "../custom.h"

LV_IMG_DECLARE(my_art); // defined in another .c file in this folder

void custom_central_draw(lv_obj_t *canvas, const struct status_state *state) {
    lv_draw_image_dsc_t img_dsc;
    lv_draw_image_dsc_init(&img_dsc);
    canvas_draw_img(canvas, 0, 44 + BUFFER_OFFSET_MIDDLE, &my_art, &img_dsc);
}
```

The middle canvas is 68x68 and is drawn in portrait, then rotated like the
other widgets.
