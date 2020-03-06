
enum status_t { UP, DOWN, UNKNOWN };

typedef struct {
    int channel;
    enum status_t status;
} heartbeat_t;

int hb_parse_heartbeat(const char* data, heartbeat_t* hb);