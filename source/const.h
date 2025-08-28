#include <limits.h>
#include <time.h>

#define MAX_PIDS 30000 
#define NO_PID 0
#define INIT_PID 1
#define NO_TRACER 0
#define NO_EVENTSUB -1 
#define MAX_SECS ( (clock_t) (LLONG_MAX/CLOCKS_PER_SEC) )
#define NR_ITIMERS 3

#define SEND_PRIORITY 1
#define SEND_TIME_SLICE 2
