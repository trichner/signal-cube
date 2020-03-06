#include "watch_dog.h"
#include "heartbeat.h"
#include "string.h"
#include "rgb_led.h"

SYSTEM_THREAD(ENABLED);

static int L_GREEN = D2;
static int L_RED = D3;

static rgb_led_t LRGB1 = {
    .pin_red = D4,
    .pin_green = D5,
    .pin_blue = D6};

static rgb_led_t LRGB2 = {
    .pin_red = A1,
    .pin_green = A0,
    .pin_blue = A2};

static int FAN = D8;

static enum status_t status[2] = {UP, UP};

void on_watch_dog_timeout(int channel)
{
  status[channel] = DOWN;
}

void on_event(const char *event, const char *data)
{

  digitalWrite(L_GREEN, LOW);
  delay(200);
  digitalWrite(L_GREEN, HIGH);

  heartbeat_t hb;
  int err = hb_parse_heartbeat(data, &hb);

  char msg[64];
  if (err)
  {
    sprintf(msg, "err: %d", err);
  }
  else
  {
    snprintf(msg, 64, "chan: %d, status: %d", hb.channel, hb.status);
    //TODO: wd_kick does not seem to work properly
    wd_kick(hb.channel, 1000 * 80, on_watch_dog_timeout);
    status[hb.channel] = hb.status;
  }

  Particle.publish("heartbeat_rx", msg, false);

  return;
}

void setup()
{

  Particle.subscribe("signal-cube", on_event, MY_DEVICES);

  pinMode(L_GREEN, OUTPUT_OPEN_DRAIN);
  pinMode(L_RED, OUTPUT_OPEN_DRAIN);

  pinMode(FAN, OUTPUT_OPEN_DRAIN);
  digitalWrite(L_GREEN, LOW);
  digitalWrite(FAN, LOW);

  // orange RGB
  rgb_setup(&LRGB1);
  rgb_set(&LRGB1, 255, 255, 0);

  rgb_setup(&LRGB2);
  rgb_set(&LRGB2, 255, 255, 0);

  wd_start(1000);
}

void loop()
{
  static int slot = 0;
  if (status[0] == UP)
  {
    if (slot % 8 == 0)
    {
      rgb_set(&LRGB1, 128, 255, 128);
    }
    else
    {
      rgb_set(&LRGB1, 0, 255, 0);
    }
  }
  else
  {
    rgb_set(&LRGB1, 255, 0, 0);
  }

  if (status[1] == UP)
  {
    if (slot % 8 == 0)
    {
      rgb_set(&LRGB2, 128, 255, 128);
    }
    else
    {
      rgb_set(&LRGB2, 0, 255, 0);
    }
  }
  else
  {
    rgb_set(&LRGB2, 255, 0, 0);
  }

  delay(500);

  if (status[0] == UP)
  {
    rgb_set(&LRGB1, 0, 255, 0);
  }
  else
  {
    rgb_set(&LRGB1, 50, 0, 0);
  }

  if (status[1] == UP)
  {
    rgb_set(&LRGB2, 0, 255, 0);
  }
  else
  {
    rgb_set(&LRGB2, 50, 0, 0);
  }
  delay(500);

  slot++;
}