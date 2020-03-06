
typedef unsigned long wd_time_t;

typedef void (*wd_handler)(int);

void wd_start(wd_time_t resolution_ms);

int wd_kick(int channel, wd_time_t timeout_ms, wd_handler handler);

void wd_stop(int channel);