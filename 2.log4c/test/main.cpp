#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "log.h"

int main(int argc, char *argv[])
{

    if (log_open("log4c_test") < 0) {
        printf("log open error!\n");
    }

    LOG_ERROR("LOG_ERROR Test");

    //定位出错位置
    if (100/0 == 0) {
        LOG_TRACE("LOG_TRACE Error!");
    }

    log_close();
    
	return 0;
}
