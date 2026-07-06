#include "coremark.h"
#include "core_portme.h"

#if VALIDATION_RUN
volatile ee_s32 seed1_volatile = 0x3415;
volatile ee_s32 seed2_volatile = 0x3415;
volatile ee_s32 seed3_volatile = 0x66;
#endif
#if PERFORMANCE_RUN
volatile ee_s32 seed1_volatile = 0x0;
volatile ee_s32 seed2_volatile = 0x0;
volatile ee_s32 seed3_volatile = 0x66;
#endif
#if PROFILE_RUN
volatile ee_s32 seed1_volatile = 0x8;
volatile ee_s32 seed2_volatile = 0x8;
volatile ee_s32 seed3_volatile = 0x8;
#endif
volatile ee_s32 seed4_volatile = ITERATIONS;
volatile ee_s32 seed5_volatile = 0;

volatile unsigned long long tohost __attribute__((section(".tohost")));
volatile unsigned long long fromhost __attribute__((section(".tohost")));

static CORETIMETYPE start_time_val;
static CORETIMETYPE stop_time_val;
ee_u32 default_num_contexts = 1;

void start_time(void) {
    start_time_val = 0;
}

void stop_time(void) {
    stop_time_val = 10;
}

CORE_TICKS get_time(void) {
    return stop_time_val - start_time_val;
}

secs_ret time_in_secs(CORE_TICKS ticks) {
    return ticks;
}

void portable_init(core_portable *p, int *argc, char *argv[]) {
    (void)argc;
    (void)argv;
    p->portable_id = 1;
}

void portable_fini(core_portable *p) {
    p->portable_id = 0;
}

int ee_printf(const char *fmt, ...) {
    (void)fmt;
    return 0;
}

void exit(int code) {
    tohost = ((unsigned long long)code << 1) | 1;
    for (;;) {
    }
}

void abort(void) {
    exit(1);
}

void *memcpy(void *dest, const void *src, ee_size_t n) {
    unsigned char *d = (unsigned char *)dest;
    const unsigned char *s = (const unsigned char *)src;
    for (ee_size_t i = 0; i < n; i++) {
        d[i] = s[i];
    }
    return dest;
}

void *memset(void *s, int c, ee_size_t n) {
    unsigned char *p = (unsigned char *)s;
    for (ee_size_t i = 0; i < n; i++) {
        p[i] = (unsigned char)c;
    }
    return s;
}
