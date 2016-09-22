#ifndef keypress_h
#define keypress_h

#ifdef __cplusplus
extern "C" {
#endif

int waitForKeypress(int timeout_msec);
/* timeout_msec < 0 : wait forever */
/* timeout_msec == 0 : don't wait */

#ifdef __cplusplus
}
#endif
#endif
