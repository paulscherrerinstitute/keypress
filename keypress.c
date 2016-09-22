#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#ifdef vxWorks
#include <selectLib.h>
#include <ioLib.h>
#else
#include <sys/select.h>
#include <termios.h>
#endif

int waitForKeypress(int timeout_msec)
{
    fd_set fdset = {{0}};
    struct timeval timeout;
    int status;
 
#ifdef FIOSETOPTIONS
    int tyOptions;
    tyOptions = ioctl(0, FIOGETOPTIONS, 0);
    ioctl(0, FIOSETOPTIONS, OPT_RAW);
#endif
#ifdef TCSANOW
    static struct termios oldt, newt;
    tcgetattr(0, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO ); /* no line mode, no echo */
    tcsetattr(0, TCSANOW, &newt);
#endif
    FD_SET(0, &fdset);
    timeout.tv_sec = timeout_msec / 1000;
    timeout.tv_usec = timeout_msec % 1000 * 1000;
    status = select(1, &fdset, NULL, NULL, timeout_msec < 0 ? NULL : &timeout);
    if (status == 1) status = getchar();
#ifdef TCSANOW
    tcsetattr(0, TCSANOW, &oldt);
#endif
#ifdef FIOSETOPTIONS
    ioctl(0, FIOSETOPTIONS, tyOptions);
#endif
    return status;
}
