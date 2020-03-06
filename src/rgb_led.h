#include <stdint.h>

typedef struct {
    uint16_t pin_red;
    uint16_t pin_green;
    uint16_t pin_blue;
} rgb_led_t;

void rgb_setup(rgb_led_t* self);
void rgb_set(rgb_led_t* self, uint8_t r, uint8_t g, uint8_t b);