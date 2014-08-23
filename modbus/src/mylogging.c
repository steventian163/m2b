#include "mylogging.h"
#include "modbus.h"
//#include <errno.h>
//
#include <stdio.h>
//#include <string.h>
//#include <stdlib.h>

void my_log_error(const char* msg)
{
        fprintf(stderr, "ERROR %s", modbus_strerror(errno));
        if (msg != NULL) {
            fprintf(stderr, ": %s\n", msg);
        } else {
            fprintf(stderr, "\n");
        }
}






