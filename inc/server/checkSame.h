#ifndef _CHECKSAME_H_
#define _CHECKSAME_H_
// 头文件
#include <stdio.h>
#include "login.h"
// 宏定义

// 函数
int checkInfo(siglelist *infoList, char *account, char *password);
int checkSame(struct siglelist *list, char *account, char *password);
#endif