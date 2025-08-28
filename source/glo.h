#ifdef _TABLE
#undef EXTERN
#define EXTERN
#endif

extern struct mproc *mp;
extern int procs_in_use;
extern char monitor_params[MULTIBOOT_PARAM_BUF_SIZE];
extern struct utsname uts_val;
extern message m_in;
extern int who_p;
extern int who_e;
extern int call_nr;
extern int (* const call_vec[])(void);
extern sigset_t core_sset;
extern sigset_t ign_sset;
extern sigset_t noign_sset;
extern u32_t system_hz;
extern int abort_flag;
extern struct machine machine;
#ifdef CONFIG_SMP
extern int cpu_proc[CONFIG_MAX_CPUS];
#endif

