
#include "heartbeat.h"
#include "string.h"
#include "stdlib.h"

#define SEPARATOR ':'

#define STR_UP "up"
#define STR_DOWN "down"
//"HEARTBEAT:0:up:..."
static const char *EVENT_HEARTBEAT = "HEARTBEAT";

static int find_separator(const char* data){
    int count = 0;
    while(*data && *data != SEPARATOR){
        data++;
        count++;
    }
    return count;
}

int hb_parse_heartbeat(const char* data, heartbeat_t* hb) {

    const char* start = data;

    int len = find_separator(data);
    if(strlen(EVENT_HEARTBEAT) < len){
        return -1;
    }

    if(strncmp(EVENT_HEARTBEAT, data, len) != 0){
        return -2;
    }
    start += len + 1;

    len = find_separator(start);
    if(len >= 8){
        return -3;
    }

    char channel_str[8];
    channel_str[7] = 0;
    strncpy(channel_str, start, len);
    int channel = atoi(channel_str);
    hb->channel = channel;

    start += len + 1;
    len = find_separator(start);

    if(strncmp(start, STR_UP, len) == 0){
        hb->status = UP;
    }else if(strncmp(start, STR_DOWN, len) == 0){
        hb->status = DOWN;
    }else{
        hb->status = UNKNOWN;
    }

    return 0;
}

