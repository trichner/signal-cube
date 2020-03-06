#include "watch_dog.h"

#include "application.h"

#define WD_CHAN_N 3

typedef struct {
  wd_time_t timeout;
  wd_time_t start;
  wd_handler handler;
} watch_dog_chan_t;

typedef struct {
  watch_dog_chan_t dogs[WD_CHAN_N];
} watch_dog_t;

static watch_dog_t wd;

void _handler(void){
  wd_time_t now = millis();

  for(int i=0;i<WD_CHAN_N;i++){
    watch_dog_chan_t dog = wd.dogs[i];
    if(dog.handler == NULL){
      // watchdog channel is disabled
      continue;
    }
    
    wd_time_t diff = now - dog.start;
    if(diff > dog.timeout){
      dog.handler(i);

      // disable after firing handler
      dog.handler = NULL;
    }
  }
}

void wd_start(wd_time_t resolution_ms) {
    for(int i=0;i<WD_CHAN_N;i++){
      bzero(&(wd.dogs[i]), sizeof(watch_dog_chan_t));
    }
    Timer(resolution_ms, _handler);
}

int wd_kick(int channel, wd_time_t timeout_ms, wd_handler handler) {
  if(channel>=WD_CHAN_N){
    return -1;
  }

  wd.dogs[channel].handler = NULL;
  wd_time_t now = millis();
  wd.dogs[channel].start = now;
  wd.dogs[channel].timeout = timeout_ms;
  wd.dogs[channel].handler = handler;
}

void wd_remove(int channel) {
  if(channel>=WD_CHAN_N){
    return;
  }
  bzero(&(wd.dogs[channel]), sizeof(watch_dog_chan_t));
}