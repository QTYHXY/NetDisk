#include "splitInfo.h"
int splitInfo(char *buf, int *num, char *account, char *password)
{
    sscanf(buf, "$%d$%[.@a-zA-Z0-9/]#%[.@a-zA-Z0-9/]", num, account, password);
    // sscanf(buf, "$%d$%s*%s|", num, account, password);
    // sscanf(buf, "$%d$%[a-zA-Z0-9_\u4e00-\u9fa5]*%[a-zA-Z0-9_\u4e00-\u9fa5]|", num, account, password);

    // printf("chooseNum=%d\n", num);
}