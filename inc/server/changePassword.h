#ifndef _CHANGEPAWWORD_H_
#define _CHANGEPAWWORD_H_
// 头文件
#include <stdio.h>
#include "login.h"
// 宏定义

// 函数
int changePassword(siglelist *infoList, char *account, char *password);
int change(struct siglelist *list, char *account, char *password);
int coverFile(struct siglelist *list);
#endif