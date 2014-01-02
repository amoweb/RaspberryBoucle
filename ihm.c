#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <pthread.h>
#include "ihm.h"

int fdMouse;
char b[3];

void IHMinit()
{
        fdMouse = open("/dev/input/mice", "r");
        fcntl(fdMouse, F_SETFL, O_NONBLOCK);
}

char IHMuserEntry()
{
        int r = read(fdMouse, b, 2);
        if(r != -1) {
                int lb=(b[0]&1)>0;
                int rb=(b[0]&2)>0;
                int mb=(b[0]&4)>0;
                if(lb)
                        return 'L';
                if(rb)
                        return 'R';
                if(mb)
                        return 'M';

        }
        return 0;
}
