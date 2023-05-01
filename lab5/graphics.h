#include <lcom/lcf.h>
#include <stdint.h>
#include "vbe.h"

int (set_graphics_mode)(uint16_t submode);

int (map_phys_mem)(uint16_t mode);

int (pixel_index)(uint16_t x, uint16_t y, uint16_t BytesPerPixel);

int (vg_draw_pixel)(uint16_t x, uint16_t y, uint32_t color);

int (vg_draw_hline)(uint16_t x, uint16_t y, uint16_t len, uint32_t color);

int (vg_draw_rectangle)(uint16_t x, uint16_t y, uint16_t width, uint16_t height, uint32_t color);

uint32_t (get_color)(uint16_t row, uint16_t col, uint8_t step, uint32_t first, uint8_t no_rectangles);

int vg_draw_pattern(uint8_t no_rectangles, uint32_t first, uint8_t step);

int (draw_xpm)(xpm_map_t xpm, uint16_t x, uint16_t y);

int (draw_xpm_loaded)(uint16_t x, uint16_t y, xpm_image_t img, uint8_t *sprite);

int (erase_screen)(uint16_t x, uint16_t y, xpm_image_t img);

bool pos_speed_update(bool verticalMovement, bool positiveMovement, uint16_t* x, uint16_t* y, uint16_t xf, uint16_t yf, int16_t speed);

bool neg_speed_update(bool verticalMovement, bool positiveMovement, uint16_t* x, uint16_t* y, uint16_t xf, uint16_t yf, int16_t speed, int* frameCounter);
