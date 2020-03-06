#include "rgb_led.h"

#include "application.h"

void rgb_setup(rgb_led_t *self)
{
  pinMode(self->pin_red, OUTPUT);
  pinMode(self->pin_green, OUTPUT);
  pinMode(self->pin_blue, OUTPUT);
  rgb_set(self, 0, 0, 0);
}

void rgb_set(rgb_led_t *self, uint8_t r, uint8_t g, uint8_t b)
{
  analogWrite(self->pin_red, 255 - r);
  analogWrite(self->pin_green, 255 - g);
  analogWrite(self->pin_blue, 255 - b);
}