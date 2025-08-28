#include <limits.h>
#include <minix/timers.h>
#include <signal.h>
#include <sys/cdefs.h>
#include "const.h"

typedef struct sigaction ixfer_sigaction;
extern ixfer_sigaction mpsigact[NR_PROCS][_NSIG];

enum mproc_flags {
    IN_USE = 0x00001,
    WAITING = 0x00002,
    ZOMBIE = 0x00004,
    PROC_STOPPED = 0x00008,
    ALARM_ON = 0x00010,
    EXITING = 0x00020,
    TOLD_PARENT = 0x00040,
    TRACE_STOPPED = 0x00080,
    SIGSUSPENDED = 0x00100,
    VFS_CALL = 0x00400,
    NEW_PARENT = 0x00800,
    UNPAUSED = 0x01000,
    PRIV_PROC = 0x02000,
    PARTIAL_EXEC = 0x04000,
    TRACE_EXIT = 0x08000,
    TRACE_ZOMBIE = 0x10000,
    DELAY_CALL = 0x20000,
    TAINTED = 0x40000,
    EVENT_CALL = 0x80000
};

#define MP_MAGIC 0xC0FFEE0

struct mproc {
    char mp_exitstatus;
    char mp_sigstatus;
    char mp_eventsub;
    pid_t mp_pid;
    endpoint_t mp_endpoint;
    pid_t mp_procgrp;
    pid_t mp_wpid;
    vir_bytes mp_waddr;
    int mp_parent;
    int mp_tracer;
    clock_t mp_child_utime;
    clock_t mp_child_stime;
    uid_t mp_realuid;
    uid_t mp_effuid;
    uid_t mp_svuid;
    gid_t mp_realgid;
    gid_t mp_effgid;
    gid_t mp_svgid;
    int mp_ngroups;
    gid_t mp_sgroups[NGROUPS_MAX];
    sigset_t mp_ignore;
    sigset_t mp_catch;
    sigset_t mp_sigmask;
    sigset_t mp_sigmask2;
    sigset_t mp_sigpending;
    sigset_t mp_ksigpending;
    sigset_t mp_sigtrace;
    ixfer_sigaction *mp_sigact;
    vir_bytes mp_sigreturn;
    minix_timer_t mp_timer;
    clock_t mp_interval[NR_ITIMERS];
    clock_t mp_started;
    unsigned int mp_flags;
    unsigned int mp_trace_flags;
    message mp_reply;
    vir_bytes mp_frame_addr;
    size_t mp_frame_len;
    signed int mp_nice;
    endpoint_t mp_scheduler;
    char mp_name[PROC_NAME_LEN];
    int mp_magic;
};

extern struct mproc mproc[NR_PROCS];

