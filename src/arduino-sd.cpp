#include <lvgl.h>
#include "core2.h"

void test_sd_partition(void);
static lv_display_t *display;

void custom_log_cb(lv_log_level_t level, const char *buffer) {
    LV_UNUSED(level);
    Serial.print("LVGL");
    Serial.println(buffer);
}

void lv_display_initialization(void) {
    lv_init();

    lv_display_t *display = hal_create_display();

    static uint16_t buf[(LV_HOR_RES_MAX * LV_VER_RES_MAX) / 10];  // Declare a buffer for 1/10 screen size
    // Initialize `display_buf` display buffer with the buffer(s).
    lv_display_set_buffers(display, buf, NULL, sizeof(buf), LV_DISPLAY_RENDER_MODE_PARTIAL);
}

void setup(void) {
    lv_display_initialization();

    hal_setup();

    lv_log_register_print_cb(custom_log_cb);
    test_sd_partition();
}

void loop(void) {
    hal_loop();

    lv_timer_handler();
    lv_tick_inc(1);
}


void test_sd_partition(void) {
    lv_obj_t* img = lv_img_create(lv_scr_act());
    lv_img_set_src(img, "S:/png/wink.png");
    lv_obj_align(img, LV_ALIGN_RIGHT_MID, -20, 0);
}